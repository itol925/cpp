#ifndef DEMO_CS_ERROR_H_H
#define DEMO_CS_ERROR_H_H

#include <iostream>


namespace stl {
    namespace error {
        enum class ErrorCode {
            success = 0,
            read_head_failed = 1,
            read_body_failed = 2,
        };

        class ErrorCategory : public std::error_category {
        public:
            const char* name() const noexcept override {
                return "ErrorCategory";
            }
            std::string message(int ev) const override {
                switch(static_cast<ErrorCode>(ev)) {
                    case ErrorCode::success:
                        return "success";
                    case ErrorCode::read_head_failed:
                        return "read head failed";
                    case ErrorCode::read_body_failed:
                        return "read body failed";
                    default:
                        return "unknown error";
                }
            }
        };

        const ErrorCategory& getErrorCategory() {
            static ErrorCategory inst;
            return inst;
        }

        std::error_code make_error_code(ErrorCode ec) {
            return std::error_code(static_cast<int>(ec), getErrorCategory());
        }

        std::error_condition make_error_condition(ErrorCode ec) {
            return {static_cast<int>(ec), getErrorCategory()};
        }
    }
}

#endif