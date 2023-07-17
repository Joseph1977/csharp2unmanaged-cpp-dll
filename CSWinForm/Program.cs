using System;


namespace ExampleTestAppWithCSWrapper
{
	class Program
	{
		static void Main(string[] args)
		{
			/// replace the following and add winform to the the project if you prefere a GUI ...

			CSUnmanagedTestClass testClass = new CSUnmanagedTestClass();
			testClass.FuncInt(42);
			testClass.FuncString("test input");
			string strReturn = testClass.FuncReturnString();
			System.Console.WriteLine("The sting returned is: " + strReturn);

			testClass.Dispose();
		}
	}
}
