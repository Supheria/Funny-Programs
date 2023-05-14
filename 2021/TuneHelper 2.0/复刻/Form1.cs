using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 复刻
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            Mm_Init();
            InitializeComponent();
            init();
        }
        //音阶
        (string,string)[] tunes = {(" C"," C"),("bD","#C"),(" D"," D"),("bE","#D"),(" E"," E"),(" F"," F"),("bG","#F"),(" G"," G"),("bA","#G"),(" A"," A"),("bB","#A"),(" B"," B")};
        //调性
        List<(List<int>, List<int>)> Mm = new List<(List<int>, List<int>)>();
        
        int[] chrdmod = { 3,4,5 };          //几和弦
        int[] convert_G = { -1, 1, 2, 3 };  //和弦转换
        List<Label> labelList_TB = new List<Label>();           //TrackBar Label 编组
        List<GroupBox> groupBoxList_G = new List<GroupBox>();   //GroupBox_G 编组（下方和弦组头）
        List<Label> labelList_G = new List<Label>();            //Label_G 编组（下方和弦内容文本）
        List<Button> buttonList = new List<Button>();           //button 编组（变调六按钮）
        bool BeginOutString = false;    //是否输出记录

        //初始化窗口数据函数
        void init()
        {
            //设置默认调性与和弦下拉框选项
            comboBox_Diaoxing.SelectedIndex = 0;
            comboBox_HeXian.SelectedIndex = 0;
            //label_TB编组
            labelList_TB.Add(label_TB_1); labelList_TB.Add(label_TB_2);
            labelList_TB.Add(label_TB_3); labelList_TB.Add(label_TB_4);
            labelList_TB.Add(label_TB_5); labelList_TB.Add(label_TB_6);
            labelList_TB.Add(label_TB_7); labelList_TB.Add(label_TB_8);
            labelList_TB.Add(label_TB_9); labelList_TB.Add(label_TB_10);
            labelList_TB.Add(label_TB_11); labelList_TB.Add(label_TB_12);
            //groupBox_G编组
            groupBoxList_G.Add(groupBox_G1); groupBoxList_G.Add(groupBox_G2);
            groupBoxList_G.Add(groupBox_G3); groupBoxList_G.Add(groupBox_G4);
            groupBoxList_G.Add(groupBox_G5); groupBoxList_G.Add(groupBox_G6);
            groupBoxList_G.Add(groupBox_G7);
            //label_G编组
            labelList_G.Add(label_G1); labelList_G.Add(label_G2);
            labelList_G.Add(label_G3); labelList_G.Add(label_G4);
            labelList_G.Add(label_G5); labelList_G.Add(label_G6);
            labelList_G.Add(label_G7);
            //button编组
            buttonList.Add(button_SSD); buttonList.Add(button_ZYWZ); buttonList.Add(button_SD);
            buttonList.Add(button_GXSSD); buttonList.Add(button_GXD); buttonList.Add(button_GXSD);
            //创建变调转换

            //布局重载

            //模拟点击主音
            textBox1.Text = "";
            BeginOutString = true;
            WritePots(0, comboBox_Diaoxing.SelectedIndex);
            WriteChords(0, comboBox_Diaoxing.SelectedIndex);
            BeginOutString = false;
            Highlight_button(button_ZYWZ);

        }
        void Mm_Init()
        {
            List<int> DD = new List<int> { 0, 2, 4, 5, 7, 9, 11 }; List<int> DDo = new List<int> { 0, 9, 1, 3}; Mm.Add((DD, DDo));
            List<int> XD = new List<int> { 0, 2, 3, 5, 7, 8, 10 }; List<int> XDo = new List<int> { 1, 3, 0, 9}; Mm.Add((XD, XDo));
            List<int> HSXD = new List<int> { 0, 2, 3, 5, 7, 8, 11 }; List<int> HSXDo = new List<int> { 2, 3, 0, 9}; Mm.Add((HSXD, HSXDo));
        }
        int shift_pre = 0;
        int index_pre = 0;
        void WritePots(int shift,int tune_index)       //写入槽
        {
            ClearDisplay();             //清空界面数据
            groupBox_CurrentMain.Text = "原主音：" + NameTune(trackBar1.Value, 0);
            //上方六个label显示
            label_XDZYWZ.Text = NameTune(0, shift);
            label_XDSSD.Text = NameTune(5, shift);
            label_XDSD.Text = NameTune(7, shift);
            //变调
            int next_Mm_index = Mm[comboBox_Diaoxing.SelectedIndex].Item2[(index_pre + 2) % Mm[comboBox_Diaoxing.SelectedIndex].Item2.Count];
            label_DX_1.Text = comboBox_Diaoxing.Items[Mm[comboBox_Diaoxing.SelectedIndex].Item2[index_pre % Mm[comboBox_Diaoxing.SelectedIndex].Item2.Count]].ToString()+"：";
            label_DX_2.Text = comboBox_Diaoxing.Items[next_Mm_index].ToString()+"：";
            //历史记录
            textBox1.Text += BeginOutString ? NameTune(shift, 0) +
                comboBox_Diaoxing.Items[Mm[comboBox_Diaoxing.SelectedIndex].Item2[index_pre % Mm[comboBox_Diaoxing.SelectedIndex].Item2.Count]].ToString()
                : "";
            switch (tune_index)
            {
                default:
                    break;
                case 0: //大调
                    label_DDZYWZ.Text = NameTune(9, shift);
                    label_DDSSD.Text = NameTune(2, shift);
                    label_DDSD.Text = NameTune(4, shift);
                    break;
                case 1: //小调
                    label_DDZYWZ.Text = NameTune(3, shift);
                    label_DDSSD.Text = NameTune(8, shift);
                    label_DDSD.Text = NameTune(10, shift);
                    break;
                case 2: //和声小调
                    label_DDZYWZ.Text = NameTune(3, shift);
                    label_DDSSD.Text = NameTune(8, shift);
                    label_DDSD.Text = NameTune(10, shift);
                    break;
            }
            //下方GroupBox 文本显示
            for (int i=0;i<groupBoxList_G.Count;i++)
            {
                groupBoxList_G[i].Text = NameTune(Mm[tune_index].Item1[i], shift);
            }
        }
        void WriteChords(int shift,int tune_index)     //写入和弦
        {
            shift_pre = shift;
            int cv = Convert_value();   //预加载和弦转换参数
            for (int i=0;i< groupBoxList_G.Count;i++)
            {
                int k = i;
                List<string> lines = new List<string>();
                lines.Add(">" + NameTune(Mm[tune_index].Item1[k], shift) + "<");
                k += 2;
                for(int j=1;j< chrdmod[comboBox_HeXian.SelectedIndex];j++)
                {
                    if (cv == j) { lines.Add(NameTune(Mm[tune_index].Item1[k%7], shift,k)); }
                    else { lines.Insert(0,NameTune(Mm[tune_index].Item1[k%7], shift, k)); }
                    k += 2;
                }
                foreach (string line in lines) { labelList_G[i].Text += line + System.Environment.NewLine; } 
            }
        }
        //根据音阶输出字符串
        string NameTune(int tune, int shift)
        {
            int l = (tune + shift) / 12;
            int o = (tune + shift) % 12 >= 0 ? (tune + shift) % 12 : (tune + shift) % 12 + 12;
            return l > 0 ?  (checkBox1.Checked ? c(l-1, " ") +    tunes[o].Item2 + c(l, "+") + " " : c(l-1, " ") +    tunes[o].Item1 + c(l, "+") +" ") :
                   l < 0 ?  (checkBox1.Checked ? c(l-1, " ") +    tunes[o].Item2 + c(l, "-") + " " : c(l-1, " ") +    tunes[o].Item1 + c(l, "-") +" ") :
                            (checkBox1.Checked ?                  tunes[o].Item2 + c(l+1, " ") :                tunes[o].Item1 + c(l+1, " "));
        }
        //根据 音阶&和弦转换 输出字符串
        string NameTune(int tune, int shift, int convert_k)
        {
            tune = convert_k < 7 ? tune - 12 : convert_k > 7 ? tune + 12 : tune; //转换和弦阶数偏移
            return NameTune(tune, shift);
        }
        //用于复制多个重复字段
        string c(int copys, string input) { string str = "";for (int i = 0; i < Math.Abs(copys); i++) { str += input; } return str; }
        //清空显示界面数据，用于保证生成数据已更新
        void ClearDisplay()     
        {
            label_XDSD.Text = "NaN";
            label_XDSSD.Text = "NaN";
            label_XDZYWZ.Text = "NaN";
            label_DDSD.Text = "NaN";
            label_DDSSD.Text = "NaN";
            label_DDZYWZ.Text = "NaN";
            for (int i = 0; i < labelList_TB.Count; i++) { labelList_TB[i].Text = NameTune(i,0); }    //重制Trackbar Labels
            foreach (GroupBox groupBox in groupBoxList_G) { groupBox.Text = "NaN"; }                //清空下方和弦组文本（GroupBox Text）
            foreach (Label label in labelList_G) { label.Text = ""; }                               //清空下方和弦内容文本（Label Text）
            groupBox_CurrentMain.Text = "原主音：NaN";     //重制Trackbar 主音指示
            foreach (Label label in labelList_TB) { label.Font = new Font(label.Font, FontStyle.Regular); } //滑动条文字复原
            if (labelList_TB.Count != 0) { labelList_TB[trackBar1.Value].Font = new Font(labelList_TB[trackBar1.Value].Font, FontStyle.Bold); } //滑动条选定文字加粗

        }
        //和弦转换值读取
        int Convert_value()
        {
            return  radioButton_Shift_Default.Checked ? convert_G[0] :
                    radioButton_Shift_First.Checked ?   convert_G[1] :
                    radioButton_Shift_Second.Checked ?  convert_G[2] :
                                                        convert_G[3] ;
        }
        void Reset_Button_Appears()
        {
            foreach(Button button in buttonList)
            {
                button.BackColor = SystemColors.Control;
                button.ForeColor = SystemColors.ControlText;
            }
        }
        void Highlight_button(Button button)
        {
            button.BackColor = System.Drawing.SystemColors.Highlight;
            button.ForeColor = System.Drawing.SystemColors.ControlLightLight;
        }
        private void button_SSD_Click(object sender, EventArgs e)
        {
            textBox1.Text += " ==上属调==> ";
            int shift = 5;
            trackBar1.Value = shift_pre % 12 >= 0 ? shift_pre % 12 : shift_pre + shift % 12 + 12;
            int tune = (shift_pre + shift) % 12 >= 0 ? (shift_pre + shift) % 12 : (shift_pre + shift) % 12 + 12;
            Reset_Button_Appears(); Highlight_button((Button)sender);
            BeginOutString = true;
            WritePots(tune, index_pre);
            WriteChords(tune, index_pre);
            BeginOutString = false;
        }
        private void button_ZYWZ_Click(object sender, EventArgs e)
        {
            index_pre = 0;
            int tune = trackBar1.Value % 12 >= 0 ? trackBar1.Value % 12 : trackBar1.Value % 12 + 12;
            Reset_Button_Appears(); Highlight_button((Button)sender);
            textBox1.Text = "";
            BeginOutString = true;
            WritePots(tune, comboBox_Diaoxing.SelectedIndex);
            WriteChords(tune, comboBox_Diaoxing.SelectedIndex);
            BeginOutString = false;
        }

        private void button_SD_Click(object sender, EventArgs e)
        {
            textBox1.Text += " ==属调==> ";
            int shift = 7;
            trackBar1.Value = shift_pre % 12 >= 0 ? shift_pre % 12 : shift_pre + shift % 12 + 12;
            int tune = (shift_pre + shift) % 12 >= 0 ? (shift_pre + shift) % 12 : (shift_pre + shift) % 12 + 12;
            Reset_Button_Appears(); Highlight_button((Button)sender);
            BeginOutString = true;
            WritePots(tune, index_pre);
            WriteChords(tune, index_pre);
            BeginOutString = false;
        }
        private void button_GXSSD_Click(object sender, EventArgs e)
        {
            textBox1.Text += " ==关系上属调==> ";
            int next_Mm_index = Mm[comboBox_Diaoxing.SelectedIndex].Item2[(index_pre + 2) % Mm[comboBox_Diaoxing.SelectedIndex].Item2.Count];
            int shift = Mm[comboBox_Diaoxing.SelectedIndex].Item2[(index_pre + 1) % Mm[comboBox_Diaoxing.SelectedIndex].Item2.Count] + 5;
            index_pre = (index_pre + 2) % Mm[comboBox_Diaoxing.SelectedIndex].Item2.Count;
            trackBar1.Value = shift_pre % 12 >= 0 ? shift_pre % 12 : shift_pre + shift % 12 + 12;
            int tune = (shift_pre + shift) % 12 >= 0 ? (shift_pre + shift) % 12 : (shift_pre + shift) % 12 + 12;
            Reset_Button_Appears(); Highlight_button((Button)sender);
            BeginOutString = true;
            WritePots(tune, next_Mm_index);
            WriteChords(tune, next_Mm_index);
            BeginOutString = false;
        }
        private void button_GXD_Click(object sender, EventArgs e)
        {
            textBox1.Text += " ==关系调==> ";
            int next_Mm_index = Mm[comboBox_Diaoxing.SelectedIndex].Item2[(index_pre + 2) % Mm[comboBox_Diaoxing.SelectedIndex].Item2.Count];
            int shift = Mm[comboBox_Diaoxing.SelectedIndex].Item2[(index_pre + 1) % Mm[comboBox_Diaoxing.SelectedIndex].Item2.Count];
            index_pre = (index_pre + 2) % Mm[comboBox_Diaoxing.SelectedIndex].Item2.Count;
            trackBar1.Value = shift_pre % 12 >= 0 ? shift_pre % 12 : shift_pre + shift % 12 + 12;
            int tune = (shift_pre + shift) % 12 >= 0 ? (shift_pre + shift) % 12 : (shift_pre + shift) % 12 + 12;
            Reset_Button_Appears(); Highlight_button((Button)sender);
            BeginOutString = true;
            WritePots(tune, next_Mm_index);
            WriteChords(tune, next_Mm_index);
            BeginOutString = false;
        }
        private void button_GXSD_Click(object sender, EventArgs e)
        {
            textBox1.Text += " ==关系属调==> ";
            int next_Mm_index = Mm[comboBox_Diaoxing.SelectedIndex].Item2[(index_pre + 2) % Mm[comboBox_Diaoxing.SelectedIndex].Item2.Count];
            int shift = Mm[comboBox_Diaoxing.SelectedIndex].Item2[(index_pre + 1) % Mm[comboBox_Diaoxing.SelectedIndex].Item2.Count] + 7;
            index_pre = (index_pre + 2) % Mm[comboBox_Diaoxing.SelectedIndex].Item2.Count;
            trackBar1.Value = shift_pre % 12 >= 0 ? shift_pre % 12 : shift_pre + shift % 12 + 12;
            int tune = (shift_pre + shift) % 12 >= 0 ? (shift_pre + shift) % 12 : (shift_pre + shift) % 12 + 12;
            Reset_Button_Appears(); Highlight_button((Button)sender);
            BeginOutString = true;
            WritePots(tune, next_Mm_index);
            WriteChords(tune, next_Mm_index);
            BeginOutString = false;
        }
        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            shift_pre = trackBar1.Value; index_pre = 0;
            Reset_Button_Appears(); Highlight_button(button_ZYWZ);
            textBox1.Text = "";
            BeginOutString = true;
            WritePots(shift_pre,0);
            WriteChords(shift_pre,0);
            BeginOutString = false;
        }
        private void comboBox_Diaoxing_SelectedIndexChanged(object sender, EventArgs e)
        {
            shift_pre = trackBar1.Value; index_pre = 0;
            Reset_Button_Appears(); Highlight_button(button_ZYWZ);
            textBox1.Text = "";
            BeginOutString = true;
            WritePots(shift_pre, comboBox_Diaoxing.SelectedIndex);
            WriteChords(shift_pre, comboBox_Diaoxing.SelectedIndex);
            BeginOutString = false;
        }
        private void comboBox_HeXian_SelectedIndexChanged(object sender, EventArgs e)
        {
            shift_pre = trackBar1.Value; index_pre = 0;
            Reset_Button_Appears(); Highlight_button(button_ZYWZ);
            textBox1.Text = "";
            BeginOutString = true;
            WritePots(shift_pre, comboBox_Diaoxing.SelectedIndex);
            WriteChords(shift_pre, comboBox_Diaoxing.SelectedIndex);
            BeginOutString = false;
        }
        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
                WritePots(shift_pre, 0);
                WriteChords(shift_pre, 0);
        }
        private void radioButton_Shift_Default_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton_Shift_Default.Checked)
            {
                WritePots(shift_pre, 0);
                WriteChords(shift_pre, 0);
            }
        }
        private void radioButton_Shift_First_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton_Shift_First.Checked)
            {
                WritePots(shift_pre, 0);
                WriteChords(shift_pre, 0);
            }
        }
        private void radioButton_Shift_Second_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton_Shift_Second.Checked)
            {
                WritePots(shift_pre, 0);
                WriteChords(shift_pre, 0);
            }
        }
        private void radioButton_Shift_Third_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton_Shift_Third.Checked)
            {
                WritePots(shift_pre, 0);
                WriteChords(shift_pre, 0);
            }
        }
        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            TopMost = checkBox2.Checked;
        }
    }
}