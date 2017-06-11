using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace SDKDemo
{
    /// <summary>
    /// MainWindow.xaml 的互動邏輯
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void btnInit_Click(object sender, RoutedEventArgs e)
        {
            int ReturnCode = MDC.Init();
            Console.WriteLine("mdc_init:{0}", ReturnCode);
        }

        private void btnClose_Click(object sender, RoutedEventArgs e)
        {
            int ReturnCode = MDC.Close();
            Console.WriteLine("mdc_init:{0}", ReturnCode);
        }

        private void btnDestory_Click(object sender, RoutedEventArgs e)
        {
            int ReturnCode = MDC.Destory();
            Console.WriteLine("mdc_init:{0}", ReturnCode);
        }
    }

    public class MDC
    {
        public const string DLL = "libmdc.dll";

        [DllImport(DLL, SetLastError = true, CallingConvention = CallingConvention.StdCall, EntryPoint = "mdc_init")]
        public static extern int Init();

        [DllImport(DLL, SetLastError = true, CallingConvention = CallingConvention.StdCall, EntryPoint = "mdc_close")]
        public static extern int Close();

        [DllImport(DLL, SetLastError = true, CallingConvention = CallingConvention.StdCall, EntryPoint = "mdc_destory")]
        public static extern int Destory();
    }
}
