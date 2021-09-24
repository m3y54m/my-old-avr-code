using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;
using System.Threading;
using System.Linq;
using System.Globalization;

namespace Oscilloscope
{
    public partial class Form1 : Form
    {
        int x, y, tempx = 255, tempy;
        float t = 0;
        SolidBrush sb = new SolidBrush(Color.Red);
        Pen pen = new Pen(Color.Red);
        System.IO.StreamWriter objWriter;
        int ScreenWidth = 900;
        int ScreenHeight = 300;
        Bitmap bmpScreen = new Bitmap(900, 300);
        Graphics gfx;
        UInt32 sampleCount = 100;
        int[] currentArray;
        int[] voltageArray;
        Queue<int> adc0Q = new Queue<int>();
        Queue<int> adc1Q = new Queue<int>();
        bool buttonStart = false;
        bool threadStarted = false;
        int count = 0;

        Queue<byte> qBuffer = new Queue<byte>();
        List<byte[]> buffer = new List<byte[]>();
        AutoResetEvent dataAvailable = new AutoResetEvent(false);
        Thread processThread;

        byte data;

        byte[] packet = new byte[8];

        void scanSerialPorts()
        {
            string[] ports = SerialPort.GetPortNames();

            cmbPortName.Items.Clear();
            cmbPortName.Items.AddRange(ports);

            if (ports.GetLength(0) == 0)
                MessageBox.Show("No Serial Port Found!");
            else
                cmbPortName.Text = ports[ports.GetLength(0) - 1];
        }
        public Form1()
        {
            InitializeComponent();
            scanSerialPorts();
            gfx = Graphics.FromImage(bmpScreen);
            pictureBox1.Image = bmpScreen;
        }

        byte getHexValue(byte chr)
        {
            byte n = 16;

            switch (Convert.ToChar(chr))
            {
                case 'F':
                    n = 15;
                    break;
                case 'E':
                    n = 14;
                    break;
                case 'D':
                    n = 13;
                    break;
                case 'C':
                    n = 12;
                    break;
                case 'B':
                    n = 11;
                    break;
                case 'A':
                    n = 10;
                    break;
                case '9':
                    n = 9;
                    break;
                case '8':
                    n = 8;
                    break;
                case '7':
                    n = 7;
                    break;
                case '6':
                    n = 6;
                    break;
                case '5':
                    n = 5;
                    break;
                case '4':
                    n = 4;
                    break;
                case '3':
                    n = 3;
                    break;
                case '2':
                    n = 2;
                    break;
                case '1':
                    n = 1;
                    break;
                case '0':
                    n = 0;
                    break;
            }

            return n;
        }

        // This thread processes the stored chunks doing the less locking possible
        void processSerialData(object state)
        {
            while (true)
            {
                dataAvailable.WaitOne();

                lock (qBuffer)
                {
                    while (qBuffer.Count() > 0)
                    {
                        data = qBuffer.Dequeue();
                        this.Invoke(new EventHandler(processData));
                    }
                 }
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            if (serialPort1.BytesToRead > 0)
            {
                byte[] chunk = new byte[serialPort1.BytesToRead];
                serialPort1.Read(chunk, 0, chunk.Length);

                lock (qBuffer)
                {
                    for (int i = 0; i < chunk.Length; i++)
                        qBuffer.Enqueue(chunk[i]);
                }

                dataAvailable.Set();
            }
        }

        private void processData(object sender, EventArgs e)
        {
            if (buttonStart)
            {

                objWriter.WriteLine(data.ToString());

            }
        }
        

        private void button1_Click(object sender, EventArgs e)
        {
            if (!buttonStart)
            {
                gfx.Clear(pictureBox1.BackColor);
                ScopeInit();
                pictureBox1.Image = bmpScreen;

                qBuffer.Clear();

                buttonStart = true;
                button1.Text = "Stop";

                button3.Enabled = true;

                x = 0;
                t = 0;
                if (serialPort1.IsOpen)
                    serialPort1.Close();

                serialPort1.PortName = cmbPortName.Text;
                serialPort1.ReadBufferSize = 1000000;
                cmbPortName.Enabled = false;
                
                button2.Enabled = false;
                if (!Directory.Exists("OUTPUT"))
                {
                    Directory.CreateDirectory("OUTPUT");
                }

                processThread = new Thread(processSerialData);
                processThread.Start();
                threadStarted = true;

                if (!serialPort1.IsOpen)
                   serialPort1.Open();

                int name = 0;

                while (File.Exists("OUTPUT\\PERIOD_" + name.ToString() + ".dat"))
                {
                    name++;
                }

                objWriter = new StreamWriter("OUTPUT\\PERIOD_" + name.ToString() + ".dat", false, Encoding.ASCII);
                //objWriter.WriteLine("t,v,i");

            }
            else
            {
                buttonStart = false;
                button1.Text = "Start";

                button3.Enabled = false;

                cmbPortName.Enabled = true;
                button2.Enabled = true;

                objWriter.Close();

                if (threadStarted)
                {
                    processThread.Abort();
                    threadStarted = false;
                }
            }
        }

        private void ScopeInit()
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            scanSerialPorts();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            pictureBox1.Image = bmpScreen;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort1.IsOpen)
                serialPort1.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (buttonStart)
            {
                button3.Enabled = false;
            }
        }
    }
}
