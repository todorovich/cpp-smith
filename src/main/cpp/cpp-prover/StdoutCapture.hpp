#pragma once

#include <string>
#include <stdexcept>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <print>

namespace prover
{
    class StdoutCapture
    {
        int   original_fd{-1};   // real stdout
        int   fd{-1};            // memfd OR tmpfile fd
        FILE* file{nullptr};     // only used in tmpfile fallback

        static int try_memfd() {
#ifdef __NR_memfd_create
            int fd = syscall(__NR_memfd_create, "stdout_capture", FD_CLOEXEC);
            if (fd != -1)
                return fd;
#endif
            return -1;
        }

        static int tmpfile_fd(FILE*& file) {
            file = ::tmpfile();
            if (!file)
                throw std::runtime_error("tmpfile() failed");

            const int fd = ::fileno(file);
            if (fd == -1)
                throw std::runtime_error("fileno(tmpfile) failed");

            return fd;
        }

        void save_original() {
            original_fd = ::dup(::fileno(stdout));
            if (original_fd == -1)
                throw std::runtime_error("dup(original stdout) failed");
        }

        void redirect_stdout_to(int new_fd) {
            ::fflush(stdout);
            if (::dup2(new_fd, ::fileno(stdout)) == -1)
                throw std::runtime_error("dup2(new_fd → stdout) failed");
        }

        std::string consume_and_clear() {
            ::fflush(stdout);

            // find size
            const off_t size = ::lseek(fd, 0, SEEK_END);
            if (size <= 0)
                return {};

            ::lseek(fd, 0, SEEK_SET);

            std::string out;
            out.resize(size);

            ssize_t n = ::read(fd, out.data(), size);
            if (n < 0)
                throw std::runtime_error("read(capture fd) failed");

            // truncate + reset pointer
            ::ftruncate(fd, 0);
            ::lseek(fd, 0, SEEK_SET);

            return out;
        }

        void restore_stdout() {
            ::fflush(stdout);
            if (original_fd != -1)
                ::dup2(original_fd, ::fileno(stdout));
        }

    public:
        StdoutCapture() {
            save_original();

            // Try memfd first
            fd = try_memfd();
            if (fd == -1) {
                // fallback to tmpfile
                fd = tmpfile_fd(file);
            }

            redirect_stdout_to(fd);
        }

        ~StdoutCapture() {
            restore_stdout();

            if (original_fd != -1)
                ::close(original_fd);

            if (file)
                ::fclose(file);   // closes its fd too
            else if (fd != -1)
                ::close(fd);
        }

        std::string read()
        {
            return consume_and_clear();
        }
    };
}
