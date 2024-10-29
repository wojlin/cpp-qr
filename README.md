# CPP QR CODE GENERATOR

## Project Setup:

    1. Clone the repository:

        ```bash
        git clone git@github.com:wojlin/cpp-qr.git
        cd cpp-qr
        ```

    2. Add Google Test as a submodule:

        ```bash
        git submodule add https://github.com/google/googletest.git external/googletest
        git submodule update --init --recursive
        ```
    
    3. Compile & Build the project:

        ```bash
        mkdir build
        cd build
        cmake ..
        make
        ```

## Running Tests:

    ```bash
    cd cpp-qr/build
    ctest
    ```