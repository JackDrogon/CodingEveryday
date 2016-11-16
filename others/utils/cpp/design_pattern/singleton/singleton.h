#include <memory>

namespace nepenthe {

namespace design_pattern {

// @doc: can be deliver
template<typename Type>
class Singleton {
public:
	static std::shared_ptr<Type> Instance()
	{
		if (instance_.get() == nullptr) {
			instance_.reset(new Type());
		}

		return instance_;
	}

protected:
	Singleton();
private:
	static std::shared_ptr<Type> instance_;
};

template<typename Type>
std::shared_ptr<Type> Singleton<Type>::instance_ = nullptr;

} // design_pattern

} // nepenthe
