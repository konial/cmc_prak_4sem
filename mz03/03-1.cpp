#include <vector>
#include <cstdint>

void
process(const std::vector<uint64_t> &vec1, std::vector<uint64_t> &vec2, int stp)
{
    if (vec2.begin() == vec2.end() || vec1.begin() == vec1.end()) {
        return;
    }
    auto vec_it = vec2.end();
    for (auto it = vec1.begin();; it += stp) {
        *--vec_it += *it;
        if (std::distance(it, vec1.end()) <= stp
            || vec_it == vec2.begin()) {
            break;
        }
    }
}
