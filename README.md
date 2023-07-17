# C# and C++ Interoperability Template
This project serves as a template for a C# application that interacts with an unmanaged C++ DLL, including support for callbacks from the DLL to the C# application.

## Description
This template provides a starting point for a C# application to interact with an unmanaged C++ DLL. It demonstrates various aspects of C# and C++ interoperability, including calling C++ functions from C# code, passing simple data types and complex structures, as well as handling callbacks from C++ to C#.

## Getting Started
To get a local copy up and running, follow these steps:

### Prerequisites
- .NET SDK
- Visual Studio 2022 or later

### Installation
1. Clone the repository to your local machine: `git clone https://github.com/Joseph1977/csharp2unmanaged-cpp-dll`
2. Open the solution file in Visual Studio.
3. Build the solution (Build -> Build Solution).

### Note:
> Currently, both the C# application and the C++ DLL are compiled as
> 32-bit. If you need to compile/use as 64-bit, make sure both the DLL
> and the C# project are set to the same platform. Otherwise, it will
> not work due to convention issues such as address: `IntPtr`/Reference
> etc.

## Usage
Run the C# project from Visual Studio. The console output will demonstrate the calls to the C++ DLL and the callbacks from the DLL to the C# code.
1. Make sure the 'CPPUnmanagedDLL.dll' DLL is in the $TargetDir of the C# application
2. First thing is to get the instance of C++ by calling `CreateInstance(callbackDelegate);` (we build it this way to allow creating multiple C++ instances and be more flexable by using same GUI with multiple C++ instances)
3. Call the set callbacks function if you want to set the other callback, you can move this structure to the CreateInstance, I separate them to demonstrate different options.

## Contributing
We welcome contributions from the community. **TBD ->**  ~~Please read our [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct and the process for submitting pull requests~~.

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.