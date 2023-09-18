#include <iostream>
#include <chrono>
#include <utility>

namespace demo {
    namespace trans {
        using std::chrono::high_resolution_clock;
        using std::chrono::time_point;
        using std::chrono::duration_cast;
        using std::chrono::milliseconds;

        void cb1 (const std::string& type, const std::string& name, bool success, long duration, int bytes) {
            std::cout << "cb1:" << type << "," << name << "," << success << "," << duration << "," << bytes << std::endl;
        }
        void cbDefault(const std::string& type, const std::string& name, bool success, long duration) {
            std::cout << "cbDefault:" << type << "," << name << "," <<  success << "," << duration << std::endl;
        }

        template<typename T = int>
        class Transaction {
        public:
            using TransactionCallbackT = std::function<void(const std::string&, const std::string&, bool, long, T)>;
            using TransactionCallback = std::function<void(const std::string&, const std::string&, bool, long)>;
            Transaction(const std::string& type, const std::string& name, TransactionCallbackT cb_t) noexcept
                : type_(type), name_(name),  cb_t_(std::move(cb_t)) {
                data_ = T();
                is_done_ = false;
                is_owner_ = true;
                start_time_ = high_resolution_clock::now();
            }
            // 默认上报 raptor
            Transaction(const std::string& type, const std::string& name, TransactionCallback cb = cbDefault) noexcept
                : type_(type), name_(name), cb_(std::move(cb)) {
                is_done_ = false;
                is_owner_ = true;
                start_time_ = high_resolution_clock::now();
            }
            Transaction(Transaction&& trans) noexcept {
                name_ = std::move(trans.name_);
                type_ = std::move(trans.type_);
                start_time_ = trans.start_time_;
                is_done_ = trans.is_done_;
                is_owner_ = trans.is_owner_;
                data_ = trans.data_;

                if (trans.cb_ != nullptr) {
                    cb_ = std::move(trans.cb_);
                } else {
                    cb_ = nullptr;
                }

                if (trans.cb_t_ != nullptr) {
                    cb_t_ = std::move(trans.cb_t_);
                } else {
                    cb_t_ = nullptr;
                }
                trans.is_owner_ = false;
            }
            void done() {
                is_done_ = true;
            }
            void done(T data) {
                is_done_ = true;
                data_ = data;
            }

            // non default constructor
            Transaction() = delete;
            Transaction(const Transaction &) = delete;
            Transaction &operator=(const Transaction &) = delete;
            Transaction &operator=(Transaction &&) = delete;

            ~Transaction() noexcept {
                if (is_owner_) {
                    auto end_time = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>(end_time - start_time_);
                    if (cb_t_ != nullptr) {
                        cb_t_(type_, name_, is_done_, duration.count(), data_);
                    }
                    if (cb_ != nullptr) {
                        cb_(type_, name_, is_done_, duration.count());
                    }
                }
            }
        private:
            std::string type_;
            std::string name_;
            bool is_done_;
            bool is_owner_;
            T data_;
            time_point<high_resolution_clock> start_time_;
            TransactionCallbackT cb_t_ = nullptr;
            TransactionCallback cb_ = nullptr;
        };



        void test() {
            Transaction<int> trans("type", "name", cb1);
            Transaction trans2 = std::move(trans);
            trans2.done(3);

            Transaction trans3("type1", "name1");
            Transaction trans4 = std::move(trans3);
            trans4.done();
            //Transaction<int> trans3 = trans2;
        }
    }
}