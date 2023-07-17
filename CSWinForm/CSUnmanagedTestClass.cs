using System;
using System.Runtime.InteropServices;


namespace ExampleTestAppWithCSWrapper
{
    public enum eErrorCode : int
    {
        /// <summary>
        /// No error.
        /// </summary>
        eSUCCESS = 0,
        /// <summary>
        /// Mucst call CreateInstance and pass the instance reference.
        /// </summary>
        eINSTANCENOTPROVIDED,
        /// <summary>
        /// One or more of the parameters are missing or incorrect
        /// </summary>
        eINVALIDPARAMETER,
    };

    public class CSUnmanagedTestClass : IDisposable
	{
        #region PInvokes
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void FuncCallbackDelegate(int nValue, string strValue);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void FuncCallbackType1Delegate(string strValue);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void FuncCallbackType2Delegate(int nValue);

        [StructLayout(LayoutKind.Sequential)]
        public struct CallbackStruct
        {
            public FuncCallbackType1Delegate Function1;
            public FuncCallbackType2Delegate Function2;
        }


        [DllImport("CPPUnmanagedDLL.dll")] // or CallingConvention.StdCall, if your C++ code is using that
        static private extern IntPtr CreateInstance(FuncCallbackDelegate callbackDelegate);

		[DllImport("CPPUnmanagedDLL.dll")]
		static private extern eErrorCode DisposeInstance(IntPtr pTestClassObject);

        [DllImport("CPPUnmanagedDLL.dll")]
        public static extern void FuncSetCallbacks(IntPtr pTestClassObject, CallbackStruct callbacks);

        [DllImport("CPPUnmanagedDLL.dll", CharSet = CharSet.Ansi)]
        static private extern string FuncReturnString(IntPtr pTestClassObject);

        [DllImport("CPPUnmanagedDLL.dll", CallingConvention = CallingConvention.StdCall)]
        static private extern eErrorCode FuncInt(IntPtr pTestClassObject, int nValue);


        [DllImport("CPPUnmanagedDLL.dll", CharSet = CharSet.Ansi)]
		static private extern eErrorCode FuncString(IntPtr pTestClassObject, string strValue);
		#endregion PInvokes

		#region Members
		private IntPtr m_pNativeObject;     // Variable to hold the C++ class's this pointer
		private FuncCallbackDelegate callbackDelegate;
        CallbackStruct callBacksStructure;

        #endregion Members

        public CSUnmanagedTestClass()
		{
            // Create an instance of this class through an exported function
            callbackDelegate = new FuncCallbackDelegate(FuncCallbackMsg);
            this.m_pNativeObject = CreateInstance(callbackDelegate);

            this.callBacksStructure = new CallbackStruct
            {
                Function1 = new FuncCallbackType1Delegate(FuncCallbackType1),
                Function2 = new FuncCallbackType2Delegate(FuncCallbackType2)
            };
            FuncSetCallbacks(this.m_pNativeObject, this.callBacksStructure);
        }

		public void Dispose()
		{
			Dispose(true);
		}

		protected virtual void Dispose(bool bDisposing)
		{
			if(this.m_pNativeObject != IntPtr.Zero)
			{
				// Call the DLL Export to dispose this class
				DisposeInstance(this.m_pNativeObject);
				this.m_pNativeObject = IntPtr.Zero;
                this.callbackDelegate = null;
                callBacksStructure.Function1 = null;
                callBacksStructure.Function2 = null;
            }

			if(bDisposing)
			{
				// No need to call the finalizer since we've now cleaned
				// up the unmanaged memory
				GC.SuppressFinalize(this);
			}
		}

		// This finalizer is called when Garbage collection occurs, but only if
		// the IDisposable.Dispose method wasn't already called.
		~CSUnmanagedTestClass()
		{
			Dispose(false);
		}

		/// <summary>
		/// this function will be call from the unmanaged DLL
		/// </summary>
		/// <param name="nValue"></param>
		/// <param name="strValue"></param>
        private void FuncCallbackMsg(int nValue, string strValue)
		{
            System.Console.WriteLine("Callback from DLL: nValue = {0}, strValue = {1} ", nValue, strValue);
        }
        private void FuncCallbackType1(string strValue)
        {
            System.Console.WriteLine("Callback Type1 from DLL: strValue = {0} ", strValue);
        }
        private void FuncCallbackType2(int nValue)
        {
            System.Console.WriteLine("Callback Type2 from DLL: nValue = {0} ", nValue);
        }


        #region Wrapper methods
        public void FuncInt(int nValue)
		{
            FuncInt(this.m_pNativeObject, nValue);
		}

		public void FuncString(string strValue)
		{
            FuncString(this.m_pNativeObject, strValue);
		}

		public string FuncReturnString()
		{
			return FuncReturnString(this.m_pNativeObject);
		}
		#endregion Wrapper methods
	}
}
