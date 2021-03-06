#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
// https://github.com/pybind/pybind11/issues/1042#issuecomment-642215028
template <typename Sequence>
inline pybind11::array_t<typename Sequence::value_type> as_pyarray(Sequence &&seq) {
    auto size                         = seq.size();
    auto data                         = seq.data();
    std::unique_ptr<Sequence> seq_ptr = std::make_unique<Sequence>(std::move(seq));
    auto capsule                      = pybind11::capsule(seq_ptr.get(), [](void *p) { std::unique_ptr<Sequence>(reinterpret_cast<Sequence *>(p)); });
    seq_ptr.release();
    return pybind11::array(size, data, capsule);
}
