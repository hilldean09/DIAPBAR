Given the simplistic nature of a progress bar in the grand scheme, no extreme measures are required to defend against exploits and the like. The primary threat model considered in DIAPBAR is comprised dependencies. The primary defensive measure is minimising the necessity, number, and obfuscation of included dependencies, even those of the C++ standard library.

While placing a degree of distrust in the C++ standard library is possibly overkill, to maximise the applicability of DIAPBAR in use cases where the aforementioned threat model is considered non-negligible, it is upheld.

Fortunately, modern C++ compilers comply comply well to this threat model by only compiling what is used, thus the following development principles can be considered as adequate:
1. Use external library features only when necessary, not just when convenient (or even performant) (e.g. intentional compatibility with a given library).
2. Segregate the use of multiple libraries where possible (e.g. not utilising std::string for std::string_view functionality).
3. Clearly implying to developers what dependencies are included in a given feature at a glance (e.g. std::string related functions clearly containing "string" in their name).

Principles *1* and *2* aim to minimise dependency number and necessity while principle *3* aims to minimise dependency obfuscation.

While these measures will likely be unnecessary in most applications, possibly even detrimental in some, they again, will be upheld as a core design principle.