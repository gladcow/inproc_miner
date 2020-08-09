#include <boost/python.hpp>
#include <memory>
#include <stratum_client.h>

using namespace boost::python;

class miner_wrapper{
public:
    miner_wrapper(const std::string& server, const std::string& port,
        const std::string& login, const std::string& pwd, double target_cpu_usage) :
        impl_(std::make_shared<stratum::stratum_client>(server, port, login, pwd, target_cpu_usage)) {
        }
    void reconnect() {
        impl_->async_reconnect();
    }
private:
    std::shared_ptr<stratum::stratum_client> impl_;
};

BOOST_PYTHON_MODULE(StratumLib) {
    class_<miner_wrapper>("Miner", init<std::string, std::string, std::string, std::string, double>()).
       def("reconnect", &miner_wrapper::reconnect);
}
