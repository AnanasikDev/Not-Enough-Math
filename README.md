# Not Enough Math

C++ 20 zero-dependency cross platform cross compiler* template math library for graphics, games, simulations, visualization and research.

Quality criteria (from most to least important):
1. Full math suite for real-time graphical applications
2. Zero-dependency, lightweight
3. Reliable and robust
4. Fast
5. Intuitive and easy to use
6. Flexible and customizable
7. Accurate
8. Cross-platform
9. Cross-compiler

Zero-dependency is the top-most priority as it is designed to be used in ultra lightweight applications. Without such restriction, other libraries may offer greater flexibility or feature set.

As seen, accuracy is of low importance, because in games and graphics performance is far more important than accuracy, and often these two cannot be achieved at once.

Reliability and robustness is achieved via extensive automatic testing against precalculated values and trusted libraries, and by active use in real projects.

Clang/GCC for Windows is first priority, then MSVC, then Linux.

*- some features are implemented using compiler-specific builtins. Currently GCC, Clang and MSVC are supported (Clang is used in development and therefore is most tested).

## Features

- No dependency on std or CRT
- Scalar operations
- Trigonometry
- Customizable error handling
- Vectors
- Matrices
- Quaternions
- Easing

Project is in development.

[Documentation](https://ananasikdev.github.io/Not-Enough-Math/)

## Roadmap

Ordered (from most to least important):

Core:

- [ ] **Basic scalar utils**
    - [X] **Comparisons, overflow, signs, lerping**
    - [X] **Sin, cos**
    - [ ] **Powers, logarithms, roots**
- [ ] **Full matrix & quaternion feature set for graphics**
- [ ] **Test scalars against std**
- [ ] **Test linear algebra against glm**
- [ ] Advanced trigonometry (inverse functions, tangents, reciprocals)
- [X] Easing
- [ ] Random and noises
    - [ ] **ND White noise**
    - [ ] 1-3D Perlin noise
    - [ ] 2-3D? Voronoi noise
    - [ ] ND Simplex noise
- [ ] Colors
    - [ ] Transformations (grayscale, gamma/linear, luminance)
    - [ ] Lerping, gradients, RGB<->HSV
    - [ ] Packed, palette
- [ ] Hashing
    - [ ] **Fast hashing for maps**

Geometry extensions:

- [ ] Vector utils same as scalar
- [ ] 2D and 3D geometry
    - [ ] **Intersection points**
    - [ ] Intersection overlays
    - [ ] Distances to shapes
    - [ ] SDFs
    - [ ] Analysis (center of mass, interior/exterior quantity, aerodynamics)
- [ ] Complex numbers
- [ ] Fractals

Safety/speed extensions:

- [ ] **Safe-unsafe compile-time execution mode with zero runtime cost**
- [ ] **Advanced constexpr algebra**

Algebra & Calculus extensions:

- [ ] Non-convertable scalable unit systems
- [ ] Analytic & discrete derivatives, integrals
- [ ] Dynamic Taylor series
- [ ] Fourier transform

Low-level speed extensions:

- [ ] Full support for SIMD backend (for x86 and ARM)
- [ ] Full use of compiler intrinsics

## Projects using NEM

[Nanoite - Ultralightweight game engine](https://github.com/AnanasikDev/Nanoite)

[SIF - Substantial Instruction Format](https://github.com/AnanasikDev/Lightweight-image-workshop)

## Sources, inspiration

Unordered:

- [Interactive IEEE](https://float.exposed)
- [Romeric's fastapprox on Github](https://github.com/romeric/fastapprox)
- [Intel's paper about x87 trigonometry instructions](https://www.arithmazium.org/library/lib/x87trigonometricinstructionsvsmathfunctions.pdf)
- [Lasse Schlör's minimax tables for sin and cos](https://publik-void.github.io/sin-cos-approximations)
- [Ben Eater's and Grant Sanderson's quaternion explanation](https://eater.net/quaternions)
- [Andrey Sitnik's and Ivan Solovev's easing functions list](https://easings.net/)
- [Desmos](https://www.desmos.com/calculator)
- [Wolfram Alpha](https://www.wolframalpha.com/)
- [Anthropic Claude (limited use)](https://claude.ai/new)
- [Quake III rsqrt](https://en.wikipedia.org/wiki/Fast_inverse_square_root)
- [Cppreference](https://en.cppreference.com/cpp)
- [Godbolt](https://godbolt.org/)
- [Henry S. Warren, Jr.'s Hacker's Delight](https://github.com/lancetw/ebook-1/blob/master/02_algorithm/Hacker%27s%20Delight%202nd%20Edition.pdf)
- [Unity Math library](https://github.com/Unity-Technologies/UnityCsReference/tree/master/Runtime/Export/Math)
- [glm](https://github.com/g-truc/glm)
- [AnanaSeek4Jam's AEngine's Math](https://github.com/AnanasikDev/AEngine/blob/main/AEngine/Core/Mathf.cpp)
- [Clang compiler extensions](https://clang.llvm.org/docs/LanguageExtensions.html)
- [GCC builtins](https://github.com/gcc-mirror/gcc/blob/master/gcc/builtins.def)
- [Intel SIMD intrinsics guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html)
- [Officedaytime x86-64 SIMD instruction list](https://www.officedaytime.com/simd512e/)