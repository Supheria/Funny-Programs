using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 图片转鼠标操作
{
    public partial class Form1 : Form
    {
        Bitmap ProcImage;
        Bitmap ProcPre;
        Bitmap ProcPix;
        CDmSoft dm;
        Thread DrawPixThread;
        DateTime CountDown;
        bool DrawPixThreadFlag;
        bool StopDraw = false;
        bool Pause = false;
        public Form1()
        {
            InitializeComponent();
            Control.CheckForIllegalCrossThreadCalls = false;
            //test();
            dm = new CDmSoft();
            init();
            //test();
            DragDrop += FileDrop;
            DragEnter += FileEnter;
        }
        public void FileDrop(object sender, DragEventArgs e)
        {
            string fileName = ((System.Array)e.Data.GetData(DataFormats.FileDrop)).GetValue(0).ToString();
            ProcImage = new Bitmap(fileName);
            //ProcImage = ReadImageFile("test.png");

            numericUpDown1.Value = 0; numericUpDown1.Maximum = ProcImage.Width;
            numericUpDown2.Value = 0; numericUpDown2.Maximum = ProcImage.Height;
            numericUpDown3.Maximum = ProcImage.Width; numericUpDown4.Maximum = ProcImage.Height;
            numericUpDown3.Value = ProcImage.Width;
            numericUpDown4.Value = ProcImage.Height;
            ProcPre = (Bitmap)ProcImage.Clone();
            numSwitch(true);
            prePic();
        }
        public void FileEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                e.Effect = DragDropEffects.Copy;
            }
            else
            {
                e.Effect = DragDropEffects.None;
            }
        }
        public void InPause()
        {
            object locx, locy;
            dm.GetCursorPos(out locx, out locy);
            while (Pause)
            {
                if (StopDraw) { break; }
                else
                {
                    if (!Pause)
                    {
                        break;
                    }
                    else
                    {
                        Thread.Sleep(50);
                    }
                }
            }
            dm.MoveTo((int)locx, (int)locy);
        }
        public void DrawPix(object arg)
        {
            int Delay = (int)((object[])arg)[0];
            DrawPixThreadFlag = true;
            Bitmap img = (Bitmap)ProcImage.Clone();
            img = CutImage(img, (int)numericUpDown1.Value, (int)numericUpDown2.Value, (int)numericUpDown3.Value, (int)numericUpDown4.Value);
            if (ProcImage.Width >= ProcImage.Height)
            {
                int dHeight = (int)(((double)ProcImage.Height / (double)ProcImage.Width) * (double)numericUpDown5.Value);
                int dWidth = (int)numericUpDown5.Value;
                //img = ZoomImage(img, ProcImage.Height / ProcImage.Width * (int)numericUpDown5.Value, (int)numericUpDown5.Value);
                img = ZoomImage(img, dHeight, dWidth);
            }
            else
            {
                int dHeight = (int)numericUpDown5.Value;
                int dWidth = (int)(((double)ProcImage.Width / (double)ProcImage.Height) * (double)numericUpDown5.Value);
                img = ZoomImage(img, dHeight, dWidth);
            }
            //img = CutImage(img, 0, 10, img.Width, img.Height - 20);
            if (radioButton1.Checked) { img = 亮度二分法(img); Thread.Sleep(Delay); }
            if (radioButton2.Checked) { img = 亮度五分法(img); Thread.Sleep(Delay); }
            if (radioButton5.Checked) { img = 亮度十分法(img); Thread.Sleep(Delay); }
            double bValue = (20 - (double)trackBar1.Value) / 20;
            if (radioButton3.Checked)
            {
                CountDown = DateTime.Now;
                CountDown = CountDown.AddMilliseconds(img.Width * img.Height / 5 + (((int)numericUpDown6.Value)* img.Width * img.Height)/45);
                for (int y = 0; y < img.Height; y++)
                {
                    if (StopDraw) { break; }

                    bool isBlack = false;
                    for (int x = 0; x < img.Width; x++)
                    {
                        if (Pause) { InPause(); }
                        if (StopDraw) { break; }
                        if (img.GetPixel(x, y).GetBrightness() < bValue)
                        {
                            if (!isBlack) { dm.delay(1); dm.LeftDown(); Thread.Sleep((int)numericUpDown6.Value); dm.delay(1); }
                            dm.MoveR(1, 0);
                            isBlack = true;
                        }
                        else
                        {
                            if (isBlack) { dm.delay(1); Thread.Sleep((int)numericUpDown6.Value); dm.LeftUp(); dm.delay(1); }
                            dm.MoveR(1, 0);
                            isBlack = false;
                        }

                    }
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    Thread.Sleep(1);
                    if (StopDraw) { break; }
                    dm.MoveR(-img.Width, 1);
                }
            }
            if (radioButton4.Checked)
            {
                for (int y = 0; y < img.Height; y++)
                {
                    if (StopDraw) { break; }
                    for (int x = 0; x < img.Width; x++)
                    {
                        if (Pause) { InPause(); }
                        if (StopDraw) { break; }

                        if (img.GetPixel(x, y).GetBrightness() < bValue)
                        {
                            dm.LeftDown();
                            Thread.Sleep((int)numericUpDown6.Value);
                            dm.delay(2);
                            dm.LeftUp();
                            dm.MoveR(1, 0);
                        }
                        else
                        {
                            dm.MoveR(1, 0);
                        }
                    }
                    Thread.Sleep(1);
                    if (StopDraw) { break; }
                    dm.MoveR(-img.Width, 1);
                }
            }
            DrawPixThreadFlag = false;
            StopDraw = false;
            checkBox1.Checked = StopDraw;
        }
        public void KeyListen(object sender, EventArgs e)
        {
            if (dm.GetKeyState(45) == 1)
            {
                if (!checkBox1.Checked)
                {
                    if (DrawPixThread == null)
                    {
                        object[] paras = new object[] { (int)0 };
                        DrawPixThread = new Thread(new ParameterizedThreadStart(DrawPix));
                        DrawPixThread.Start(paras);
                    }
                    else
                    {
                        if (!DrawPixThreadFlag)
                        {
                            object[] paras = new object[] { (int)0 };
                            DrawPixThread = new Thread(new ParameterizedThreadStart(DrawPix));
                            DrawPixThread.Start(paras);
                        }
                    }
                }
            }
            if (dm.GetKeyState(35) == 1)
            {
                StopDraw = true;
                checkBox1.Checked = StopDraw;
            }
            if (dm.GetKeyState(19) == 1)
            {
                Pause = true;
                radioButton6.Checked = Pause;
            }
            if (dm.GetKeyState(36) == 1)
            {
                Pause = false;
                radioButton7.Checked = !Pause;
            }
            if(dm.GetKeyState(46)==1)
            {
                StopDraw = false;
                checkBox1.Checked = StopDraw;
            }
        }
        public void test()
        {
            //ProcImage = new Bitmap("test3.png");
            ProcImage = new Bitmap("test.jpg");
            //ProcImage = ReadImageFile("test.png");

            numericUpDown1.Value = 0; numericUpDown1.Maximum = ProcImage.Width;
            numericUpDown2.Value = 0; numericUpDown2.Maximum = ProcImage.Height;

            numericUpDown3.Value = ProcImage.Width; numericUpDown3.Maximum = ProcImage.Width;
            numericUpDown4.Value = ProcImage.Height; numericUpDown4.Maximum = ProcImage.Height;
            ProcPre = (Bitmap)ProcImage.Clone();
            numSwitch(true);
            prePic();
        }
        public void prePic() //生成预览
        {
            Bitmap img = (Bitmap)ProcPre.Clone();
            if (img.Width >= img.Height)
            {
                int dHeight = (int)((double)img.Height / (double)img.Width * 100);
                int dWidth = 100;
                img = ZoomImage(img, dHeight, dWidth);
                pictureBox1.Width = img.Width;
                pictureBox1.Height = img.Height;
                pictureBox1.Image = img;
                pictureBox1.Update();
            }
            else
            {
                int dWidth = (int)((double)img.Width / (double)img.Height * 100);
                int dHeight = 100;
                img = ZoomImage(img, dHeight, dWidth);
                pictureBox1.Width = img.Width;
                pictureBox1.Height = img.Height;
                pictureBox1.Image = img;
                pictureBox1.Update();
            }
        }
        public void prePix() //生成效果图
        {
            Bitmap img = (Bitmap)ProcPix.Clone(); ;
            if (img.Width >= img.Height)
            {
                int dHeight = (int)((double)img.Height / (double)img.Width * 200);
                int dWidth = 200;
                img = ZoomImage(img, dHeight, dWidth);
                pictureBox2.Width = img.Width;
                pictureBox2.Height = img.Height;
                pictureBox2.Image = img;
                pictureBox2.Update();
            }
            else
            {
                int dWidth = (int)((double)img.Width / (double)img.Height * 200);
                int dHeight = 200;
                img = ZoomImage(img, dHeight, dWidth);
                pictureBox2.Width = img.Width;
                pictureBox2.Height = img.Height;
                pictureBox2.Image = img;
                pictureBox2.Update();
            }
        }
        public void init() //初始化
        {
            numericUpDown1.ValueChanged += ValueChangeEvent;
            numericUpDown2.ValueChanged += ValueChangeEvent;
            numericUpDown3.ValueChanged += ValueChangeEvent;
            numericUpDown4.ValueChanged += ValueChangeEvent;
            numericUpDown5.ValueChanged += ValueChangeEvent;
            numSwitch(false);
            //判断是否按下按键
            timer1.Interval = 100;
            timer1.Tick += KeyListen;
            timer1.Start();
            //终止选项监听
            checkBox1.CheckedChanged += StopOnCheck;
        }
        public void StopOnCheck(object sender, EventArgs e) //终止选择框事件
        {
            StopDraw = checkBox1.Checked;
        }
        public void numSwitch(bool b) //数字控制开关
        {
            if (b)
            {
                numericUpDown1.Enabled = true;
                numericUpDown2.Enabled = true;
                numericUpDown3.Enabled = true;
                numericUpDown4.Enabled = true;
                numericUpDown5.Enabled = true;
            }
            else
            {
                numericUpDown1.Enabled = false;
                numericUpDown2.Enabled = false;
                numericUpDown3.Enabled = false;
                numericUpDown4.Enabled = false;
                numericUpDown5.Enabled = false;
            }
        }
        public void ValueChangeEvent(object sender, EventArgs e)
        {
            if (numericUpDown1.Value > numericUpDown3.Value - 10) { numericUpDown1.Value = numericUpDown3.Value - 10 >= 0 ? numericUpDown3.Value - 10 : 0; }
            if (numericUpDown2.Value > numericUpDown4.Value - 10) { numericUpDown2.Value = numericUpDown4.Value - 10 >= 0 ? numericUpDown4.Value - 10 : 0; }
            numericUpDown5.Maximum = ProcImage.Width > ProcImage.Height ? ProcImage.Width : ProcImage.Height;
        }

        public Bitmap ReadImageFile(string path) //读取图片
        {
            FileStream fs = File.OpenRead(path); //OpenRead
            int filelength = 0;
            filelength = (int)fs.Length; //获得文件长度 
            Byte[] image = new Byte[filelength]; //建立一个字节数组 
            fs.Read(image, 0, filelength); //按字节流读取 
            System.Drawing.Image result = System.Drawing.Image.FromStream(fs);
            fs.Close();
            Bitmap bit = new Bitmap(result);
            return bit;
        }
        public Bitmap ZoomImage(Bitmap bitmap, int destHeight, int destWidth) //缩放图片
        {
            try
            {
                System.Drawing.Image sourImage = bitmap;
                int width = 0, height = 0;
                //按比例缩放             
                int sourWidth = sourImage.Width;
                int sourHeight = sourImage.Height;
                if (sourHeight > destHeight || sourWidth > destWidth)
                {
                    if ((sourWidth * destHeight) > (sourHeight * destWidth))
                    {
                        width = destWidth;
                        height = (destWidth * sourHeight) / sourWidth;
                    }
                    else
                    {
                        height = destHeight;
                        width = (sourWidth * destHeight) / sourHeight;
                    }
                }
                else
                {
                    width = sourWidth;
                    height = sourHeight;
                }
                Bitmap destBitmap = new Bitmap(destWidth, destHeight);
                Graphics g = Graphics.FromImage(destBitmap);
                g.Clear(Color.Transparent);
                //设置画布的描绘质量           
                g.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighQuality;
                g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
                g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
                g.DrawImage(sourImage, new Rectangle((destWidth - width) / 2, (destHeight - height) / 2, width, height), 0, 0, sourImage.Width, sourImage.Height, GraphicsUnit.Pixel);
                g.Dispose();
                //设置压缩质量       
                System.Drawing.Imaging.EncoderParameters encoderParams = new System.Drawing.Imaging.EncoderParameters();
                long[] quality = new long[1];
                quality[0] = 100;
                System.Drawing.Imaging.EncoderParameter encoderParam = new System.Drawing.Imaging.EncoderParameter(System.Drawing.Imaging.Encoder.Quality, quality);
                encoderParams.Param[0] = encoderParam;
                sourImage.Dispose();
                return destBitmap;
            }
            catch
            {
                return bitmap;
            }
        }

        public Bitmap CutImage(Bitmap bmp, int x, int y, int width, int height)
        {
            //Bitmap b = new Bitmap(width-x, height-y);
            Bitmap b = (Bitmap)bmp.Clone();
            Rectangle cropRect = new Rectangle(x, y, width - x, height - y);
            Bitmap target = new Bitmap(cropRect.Width, cropRect.Height);

            using (Graphics g = Graphics.FromImage(target))
            {
                g.DrawImage(b, new Rectangle(0, 0, target.Width, target.Height),
                      cropRect,
                      GraphicsUnit.Pixel);
            }
            return target;
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            //生成预览
            ProcPre = CutImage(ProcImage, (int)numericUpDown1.Value, (int)numericUpDown2.Value, (int)numericUpDown3.Value, (int)numericUpDown4.Value);
            prePic();
            //进行运算
            if (radioButton1.Checked) { ProcPix = 亮度二分法(ProcImage); prePix(); }
            if (radioButton2.Checked) { ProcPix = 亮度五分法(ProcImage); prePix(); }
            if (radioButton5.Checked) { ProcPix = 亮度十分法(ProcImage); prePix(); }
        }
        public Bitmap 亮度二分法(Bitmap img)
        {
            Bitmap b = new Bitmap(img);
            double bValue = (20 - (double)trackBar1.Value) / 20;
            for (int y = 0; y < b.Height; y++)
            {
                for (int x = 0; x < b.Width; x++)
                {
                    float bright = b.GetPixel(x, y).GetBrightness();
                    if (bright > bValue) { b.SetPixel(x, y, Color.White); }
                    else { b.SetPixel(x, y, Color.Black); }
                }
            }
            return b;
        }
        public Bitmap 亮度五分法(Bitmap img)
        {
            Bitmap b = new Bitmap(img);
            double bValue = (20 - (double)trackBar1.Value) / 20;
            for (int y = 0; y < b.Height - 2; y += 2)
            {
                for (int x = 0; x < b.Width - 2; x += 2)
                {
                    float avgBright = (
                        b.GetPixel(x, y + 0).GetBrightness() + b.GetPixel(x + 1, y + 0).GetBrightness() +
                        b.GetPixel(x, y + 1).GetBrightness() + b.GetPixel(x + 1, y + 1).GetBrightness()) / 4;

                    if (avgBright < bValue - 0.3)
                    {
                        b.SetPixel(x, y + 0, Color.Black); b.SetPixel(x + 1, y + 0, Color.Black);
                        b.SetPixel(x, y + 1, Color.Black); b.SetPixel(x + 1, y + 1, Color.Black);
                    }
                    else if (avgBright < bValue - 0.1)
                    {
                        b.SetPixel(x, y + 0, Color.White); b.SetPixel(x + 1, y + 0, Color.Black);
                        b.SetPixel(x, y + 1, Color.Black); b.SetPixel(x + 1, y + 1, Color.Black);
                    }
                    else if (avgBright < bValue + 0.1)
                    {
                        b.SetPixel(x, y + 0, Color.White); b.SetPixel(x + 1, y + 0, Color.Black);
                        b.SetPixel(x, y + 1, Color.Black); b.SetPixel(x + 1, y + 1, Color.White);
                    }
                    else if (avgBright < bValue + 0.3)
                    {
                        b.SetPixel(x, y + 0, Color.White); b.SetPixel(x + 1, y + 0, Color.Black);
                        b.SetPixel(x, y + 1, Color.White); b.SetPixel(x + 1, y + 1, Color.White);
                    }
                    else if (avgBright < bValue + 0.5)
                    {
                        b.SetPixel(x, y + 0, Color.White); b.SetPixel(x + 1, y + 0, Color.White);
                        b.SetPixel(x, y + 1, Color.White); b.SetPixel(x + 1, y + 1, Color.White);
                    }
                }
            }
            b = CutImage(b, 0, 0, b.Width - 2, b.Height - 2);
            return b;
        }
        public Bitmap 亮度十分法(Bitmap img)
        {
            Bitmap b = new Bitmap(img);
            double bValue = (20 - (double)trackBar1.Value) / 20;
            for (int y = 0; y < b.Height - 3; y += 3)
            {
                for (int x = 0; x < b.Width - 3; x += 3)
                {

                    float avgBright = (b.GetPixel(x, y).GetBrightness() + b.GetPixel(x + 1, y).GetBrightness() + b.GetPixel(x + 2, y).GetBrightness() +
                        b.GetPixel(x, y + 1).GetBrightness() + b.GetPixel(x + 1, y + 1).GetBrightness() + b.GetPixel(x + 2, y + 1).GetBrightness() +
                        b.GetPixel(x, y + 2).GetBrightness() + b.GetPixel(x + 1, y + 2).GetBrightness() + b.GetPixel(x + 2, y + 2).GetBrightness()) / 9;
                    if (avgBright < bValue - 0.4)
                    {
                        b.SetPixel(x, y, Color.Black); b.SetPixel(x + 1, y, Color.Black); b.SetPixel(x + 2, y, Color.Black);
                        b.SetPixel(x, y + 1, Color.Black); b.SetPixel(x + 1, y + 1, Color.Black); b.SetPixel(x + 2, y + 1, Color.Black);
                        b.SetPixel(x, y + 2, Color.Black); b.SetPixel(x + 1, y + 2, Color.Black); b.SetPixel(x + 2, y + 2, Color.Black);
                    }
                    else if (avgBright < bValue - 0.3)
                    {
                        b.SetPixel(x, y, Color.Black); b.SetPixel(x + 1, y, Color.Black); b.SetPixel(x + 2, y, Color.Black);
                        b.SetPixel(x, y + 1, Color.Black); b.SetPixel(x + 1, y + 1, Color.White); b.SetPixel(x + 2, y + 1, Color.Black);
                        b.SetPixel(x, y + 2, Color.Black); b.SetPixel(x + 1, y + 2, Color.Black); b.SetPixel(x + 2, y + 2, Color.Black);
                    }
                    else if (avgBright < bValue - 0.2)
                    {
                        b.SetPixel(x, y, Color.Black); b.SetPixel(x + 1, y, Color.Black); b.SetPixel(x + 2, y, Color.White);
                        b.SetPixel(x, y + 1, Color.Black); b.SetPixel(x + 1, y + 1, Color.Black); b.SetPixel(x + 2, y + 1, Color.Black);
                        b.SetPixel(x, y + 2, Color.White); b.SetPixel(x + 1, y + 2, Color.Black); b.SetPixel(x + 2, y + 2, Color.Black);
                    }
                    else if (avgBright < bValue - 0.1)
                    {
                        b.SetPixel(x, y, Color.Black); b.SetPixel(x + 1, y, Color.Black); b.SetPixel(x + 2, y, Color.White);
                        b.SetPixel(x, y + 1, Color.Black); b.SetPixel(x + 1, y + 1, Color.White); b.SetPixel(x + 2, y + 1, Color.Black);
                        b.SetPixel(x, y + 2, Color.White); b.SetPixel(x + 1, y + 2, Color.Black); b.SetPixel(x + 2, y + 2, Color.Black);
                    }
                    else if (avgBright < bValue)
                    {
                        b.SetPixel(x, y, Color.White); b.SetPixel(x + 1, y, Color.Black); b.SetPixel(x + 2, y, Color.White);
                        b.SetPixel(x, y + 1, Color.Black); b.SetPixel(x + 1, y + 1, Color.Black); b.SetPixel(x + 2, y + 1, Color.Black);
                        b.SetPixel(x, y + 2, Color.White); b.SetPixel(x + 1, y + 2, Color.Black); b.SetPixel(x + 2, y + 2, Color.White);
                    }
                    else if (avgBright < bValue + 0.1)
                    {
                        b.SetPixel(x, y, Color.White); b.SetPixel(x + 1, y, Color.Black); b.SetPixel(x + 2, y, Color.White);
                        b.SetPixel(x, y + 1, Color.Black); b.SetPixel(x + 1, y + 1, Color.White); b.SetPixel(x + 2, y + 1, Color.Black);
                        b.SetPixel(x, y + 2, Color.White); b.SetPixel(x + 1, y + 2, Color.Black); b.SetPixel(x + 2, y + 2, Color.White);
                    }
                    else if (avgBright < bValue + 0.2)
                    {
                        b.SetPixel(x, y, Color.Black); b.SetPixel(x + 1, y, Color.White); b.SetPixel(x + 2, y, Color.White);
                        b.SetPixel(x, y + 1, Color.White); b.SetPixel(x + 1, y + 1, Color.Black); b.SetPixel(x + 2, y + 1, Color.White);
                        b.SetPixel(x, y + 2, Color.White); b.SetPixel(x + 1, y + 2, Color.White); b.SetPixel(x + 2, y + 2, Color.Black);
                    }
                    else if (avgBright < bValue + 0.3)
                    {
                        b.SetPixel(x, y, Color.Black); b.SetPixel(x + 1, y, Color.White); b.SetPixel(x + 2, y, Color.White);
                        b.SetPixel(x, y + 1, Color.White); b.SetPixel(x + 1, y + 1, Color.White); b.SetPixel(x + 2, y + 1, Color.White);
                        b.SetPixel(x, y + 2, Color.White); b.SetPixel(x + 1, y + 2, Color.White); b.SetPixel(x + 2, y + 2, Color.Black);
                    }
                    else if (avgBright < bValue + 0.4)
                    {
                        b.SetPixel(x, y, Color.White); b.SetPixel(x + 1, y, Color.White); b.SetPixel(x + 2, y, Color.White);
                        b.SetPixel(x, y + 1, Color.White); b.SetPixel(x + 1, y + 1, Color.Black); b.SetPixel(x + 2, y + 1, Color.White);
                        b.SetPixel(x, y + 2, Color.White); b.SetPixel(x + 1, y + 2, Color.White); b.SetPixel(x + 2, y + 2, Color.White);
                    }
                    else if (avgBright < bValue + 0.5)
                    {
                        b.SetPixel(x, y, Color.White); b.SetPixel(x + 1, y, Color.White); b.SetPixel(x + 2, y, Color.White);
                        b.SetPixel(x, y + 1, Color.White); b.SetPixel(x + 1, y + 1, Color.White); b.SetPixel(x + 2, y + 1, Color.White);
                        b.SetPixel(x, y + 2, Color.White); b.SetPixel(x + 1, y + 2, Color.White); b.SetPixel(x + 2, y + 2, Color.White);
                    }
                }
            }
            b = CutImage(b, 0, 0, b.Width - 3, b.Height - 3);
            return b;
        }
        private void Button2_Click(object sender, EventArgs e)
        {
            if (!checkBox1.Checked)
            {
                if (DrawPixThread == null)
                {
                    object[] paras = new object[] { (int)5000 };
                    DrawPixThread = new Thread(new ParameterizedThreadStart(DrawPix));
                    DrawPixThread.Start(paras);
                }
                else
                {
                    if (!DrawPixThreadFlag)
                    {
                        object[] paras = new object[] { (int)5000 };
                        DrawPixThread = new Thread(new ParameterizedThreadStart(DrawPix));
                        DrawPixThread.Start(paras);
                    }
                }
            }
        }
        [System.Runtime.InteropServices.DllImport("user32")]
        private static extern int mouse_event(int dwFlags, int dx, int dy, int dwData, int dwExtraInfo);
        //移动鼠标 
        const int MOUSEEVENTF_MOVE = 0x0001;
        //模拟鼠标左键按下 
        const int MOUSEEVENTF_LEFTDOWN = 0x0002;
        //模拟鼠标左键抬起 
        const int MOUSEEVENTF_LEFTUP = 0x0004;
        //模拟鼠标右键按下 
        const int MOUSEEVENTF_RIGHTDOWN = 0x0008;
        //模拟鼠标右键抬起 
        const int MOUSEEVENTF_RIGHTUP = 0x0010;
        //模拟鼠标中键按下 
        const int MOUSEEVENTF_MIDDLEDOWN = 0x0020;
        //模拟鼠标中键抬起 
        const int MOUSEEVENTF_MIDDLEUP = 0x0040;
        //标示是否采用绝对坐标 
        const int MOUSEEVENTF_ABSOLUTE = 0x8000;
        //模拟鼠标滚轮滚动操作，必须配合dwData参数
        const int MOUSEEVENTF_WHEEL = 0x0800;

        private void Button3_Click(object sender, EventArgs e)
        {
            numericUpDown5.Value = numericUpDown5.Maximum;
        }

        private void Button4_Click(object sender, EventArgs e)
        {
            numericUpDown5.Value = numericUpDown5.Maximum >= 200 ? 200 : numericUpDown5.Maximum;
        }
    }
}
