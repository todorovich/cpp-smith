#include "cpp-prover/Test.hpp"
#include "logging/Logger.hpp"
#include "cpp-prover/Assert.hpp"

#include <filesystem>
#include <fstream>

using namespace prover;
using namespace logging;

namespace logger_test
{
    void LoggerStringSinkMultiple()
    {
        std::string buffer;
        auto s = std::make_unique<StringSink>(
            std::make_unique<MinimalFormatter>(), buffer
        );

        Logger log("scope", std::move(s));

        log.print("A");
        log.print("B {}", 2);
        log.print("C {}", 3);

        Assert::areEqual<std::string>("AB 2C 3", buffer);
    }

    void loggerFileSink()
    {
        const std::string path = "logger_test_file.txt";

        {
            auto f = std::make_unique<FileSink>(
                std::make_unique<MinimalFormatter>(),
                path
            );

            Logger log("file", std::move(f));
            log.print("file {}", 55);
        }

        std::ifstream in(path);
        std::string contents(
            (std::istreambuf_iterator<char>(in)),
            std::istreambuf_iterator<char>()
        );

        Assert::areEqual<std::string>("file 55", contents);
    }

    void LoggerMultiStringAndFileSinks()
    {
        std::string buffer_1;
        // create string sinks
        auto unique_string_sink_1 = std::make_unique<StringSink>(
            std::make_unique<MinimalFormatter>(), buffer_1
        );
        std::string buffer_2;
        auto unique_string_sink_2 = std::make_unique<StringSink>(
            std::make_unique<MinimalFormatter>(), buffer_2
        );

        // file sink paths
        const std::string filepath_1 = "multi_sink_file1.txt";
        const std::string filepath_2 = "multi_sink_file2.txt";

        // create file sinks
        {
            auto file_sink_1 = std::make_unique<FileSink>(
                std::make_unique<MinimalFormatter>(),
                filepath_1
            );

            auto file_sink_2 = std::make_unique<FileSink>(
                std::make_unique<MinimalFormatter>(),
                filepath_2
            );

            // scope for log so it'll close the file so that the test can read it.
            Logger log(
                "scope",
                std::move(unique_string_sink_1),
                std::move(unique_string_sink_2),
                std::move(file_sink_1),
                std::move(file_sink_2)
            );

            log.print("combo {}", 777);
        }

        // verify string sinks
        Assert::areEqual<std::string>("combo 777", buffer_1);
        Assert::areEqual<std::string>("combo 777", buffer_2);

        // verify file sinks
        auto read_file = [](const std::string& path) {
            std::ifstream in(path);
            return std::string(
                (std::istreambuf_iterator<char>(in)),
                std::istreambuf_iterator<char>()
            );
        };

        Assert::areEqual<std::string>("combo 777", read_file(filepath_1));
        Assert::areEqual<std::string>("combo 777", read_file(filepath_2));
    }

    namespace {
        class StdoutRedirect {
            int saved_fd_;
            bool active_;
        public:
            explicit StdoutRedirect(const char* path)
            {
                saved_fd_ = dup(fileno(stdout));

                if (const FILE* file = std::freopen(path, "w", stdout); file)
                    active_ = true;
                else
                    active_ = false;
            }

            ~StdoutRedirect() {
                if (active_) {
                    fflush(stdout);
                    dup2(saved_fd_, fileno(stdout));
                    close(saved_fd_);
                }
            }

            StdoutRedirect(const StdoutRedirect&) = delete;
            StdoutRedirect& operator=(const StdoutRedirect&) = delete;
        };
    }

    void LoggerConsoleSinkRedirectsStdout()
    {
        const char* file = "console_capture.txt";
        { // to scope closing the file the test needs to read.
            StdoutRedirect redirect(file);

            auto sink = std::make_unique<ConsoleSink>(
               std::make_unique<MinimalFormatter>()
            );

            Logger log("test", std::move(sink));
            log.print("hello {}", 99234);

            std::fflush(stdout);
        }

        std::ifstream in(file);
        std::string data((std::istreambuf_iterator<char>(in)),
                         std::istreambuf_iterator<char>());

        Assert::areEqual<std::string>("hello 99234", data);
    }

    struct Tests
    {
        inline const static Test<void> logger_string_sink_multiple {"logger_string_sink_multiple", LoggerStringSinkMultiple };
        inline const static Test<void> logger_file_sink {"logger_file_sink", loggerFileSink };
        inline const static Test<void> logger_multi_string_and_file_sinks {
            "logger_multi_string_and_file_sinks", LoggerMultiStringAndFileSinks
        };
        inline const static Test<void> logger_console_sink_redirects_stdout {
            "logger_console_sink_redirects_stdout", LoggerConsoleSinkRedirectsStdout
        };
    };

    const Tests tests;
}