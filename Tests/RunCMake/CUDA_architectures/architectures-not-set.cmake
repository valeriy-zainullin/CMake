unset(CMAKE_CUDA_ARCHITECTURES)
enable_language(CUDA)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/info.cmake" "
set(CMAKE_CUDA_COMPILER_ID \"${CMAKE_CUDA_COMPILER_ID}\")
set(CMAKE_CUDA_COMPILER_VERSION \"${CMAKE_CUDA_COMPILER_VERSION}\")
set(CMAKE_CUDA_ARCHITECTURES \"${CMAKE_CUDA_ARCHITECTURES}\")
")