# Learning to use libraries on Windows and Linux

This is a repository containing examples to learn about how to use C++ libraries. 

- If you know C++, have problems with using dlls and don't know where to start learning, these examples might help you.
- If you don't know how shared libraries work or how they are structured, these examples are probably not really helping. Please refer to the links in the `information.md`.
- These examples are intended for the "working coder", i.e. they should highlight problems that might occur in code, they don't try to explain the inner workings of shared libraries.

## Structure

Two folders: 
- One gcc and one msvc++ for the corresponding compiler
- Some examples (e.g. versioning for Linux) only exist for one operating system. That's because they don't make a lot of sense for the other.
- Examples with the same name should contain roughly the same code examples (compiler specific extensions and quirks might change the code a bit).

Working with the examples:
- Each subfolder contains a file `explanations.md` which contains the directives to be used for each example and explains (roughly) what is going on.

## Contribute

If you have other examples or quirks, I'll be happy to accept PRs.