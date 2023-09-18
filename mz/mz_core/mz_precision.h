#pragma once

namespace mz {
#ifdef USE_DOUBLE_PRECISION
#pragma message("use double precision")
using real = double;
#else
#pragma message("use single precision")
using real = float;
#endif
} // namespace mz