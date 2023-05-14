// 存档记录格式（未加密）：
// 身份编号><身份状态><名称><职业编号><编辑时间
#include "dir.h"
#include "save class.h"
#include "tools.h"
#include "career.h"

SaveReg savereg;

Save::Save(
	std::string name,
	uint career,
	std::vector<ushrt> _3Q,
	uint wealth) : Player(name, career, _3Q, wealth)
{
	//savereg.ReadReg();
	//for (auto it = (*savereg.content_living).begin(); it != (*savereg.content_living).end(); it++)
	{
		//(*savereg.content_living).push_back(*it);
	}
	m_pos = 1;
	m_vrfcode = "";
	m_svdir = "";
	m_settime = 0;
	m_edittime = 0;
}
Save::~Save()
{
}

std::string Save::AcquireVrfcode()
{
	using namespace std; using namespace myTools;
	uint a = (get_num() % (m_pos ? m_pos : 1)) + get_status() + (m_edittime % (m_settime ? m_settime : 1)) + m_career + m_moral + m_3Q[0] + m_3Q[1] + m_3Q[2];
	m_vrfcode = to_string((m_wealth * a) % ((m_wealth + a) ? (m_wealth + a) : 1)) + m_name;
	return encoder(m_vrfcode);
}
std::string Save::FormRegClause()
{
	using namespace std;
	time(&m_edittime);
	return to_string(get_num()) + SPLITPATTERN_SVREG() + to_string(get_status()) + SPLITPATTERN_SVREG() + m_name + SPLITPATTERN_SVREG() + to_string(m_career) + SPLITPATTERN_SVREG() + to_string(m_edittime);
}
void Save::UpdateLivingContent()
{
	using namespace std; using namespace ieTools;
	if (get_status() == eIllegal)
	{
		string clause = FormRegClause();
		(*savereg.content_living)[m_pos - 1] = clause;
		*savereg.content_living = (*savereg.content_living);
		return;
	}
	// 新身份（num为0则代表是新身份）
	else if (!get_num())
	{
		set_num(++savereg.thelastnum);
		string clause = FormRegClause();
		(*savereg.content_living).push_back(clause);
		m_pos = (*savereg.content_living).size();
		m_settime = m_edittime;
		*savereg.content_living = (*savereg.content_living);
		return;
	}
	
	else
	{
		auto vClause = SplitString((*savereg.content_living)[m_pos - 1], SPLITPATTERN_SVREG());
		if (vClause[0] != to_string(get_num())) { illegal(); }
		string clause = FormRegClause();
		(*savereg.content_living)[m_pos - 1] = clause;
		*savereg.content_living = (*savereg.content_living);
		return;
	}
	
}
bool Save::ReadPassport()
{
	using namespace std; using namespace myTools;
	const string path = m_svdir + sv_PassportName();
	if (TestFileExistence(path) && TestFileContent(path))
	{
		ifstream fin(path);
		string num; getline(fin, num); set_num(atoi(num.c_str())); // 身份编号
		string sta; getline(fin, sta); set_status(atoi(sta.c_str())); // 身份状态
		string stt; getline(fin, stt); m_settime = _atoi64(stt.c_str()); // 存档设立时间
		getline(fin, m_name); // 名称
		string crr; getline(fin, crr); m_career = atoi(crr.c_str()); // 职业
		return true;
	}
	else
		return false;
}
bool Save::ReadAdvance()
{
	using namespace std; using namespace myTools;
	const string path = m_svdir + sv_AdvanceName();
	if (TestFileExistence(path) && TestFileContent(path))
	{
		ifstream fin(path);
		getline(fin, m_vrfcode); // 效验码
		string edt; getline(fin, edt); m_edittime = _atoi64(edt.c_str()); // 编辑时间
		string mor; getline(fin, mor); m_moral = atoi(mor.c_str()); // 道德值
		string IQ; getline(fin, IQ); m_3Q[0] = atoi(IQ.c_str()); // IQ
		string HQ; getline(fin, HQ); m_3Q[1] = atoi(HQ.c_str()); // HQ
		string EQ; getline(fin, EQ); m_3Q[2] = atoi(EQ.c_str()); // EQ
		string wea; getline(fin, wea); m_wealth = atoi(wea.c_str()); // 财富
		return true;
	}
	else
		return false;
}
bool Save::OutputPassport()
{
	using namespace std; using namespace myTools;
	const string path = m_svdir + sv_PassportName();
	ofstream fout(path);
	if (fout.is_open())
	{
		fout << get_num() << endl // 身份编号
			<< get_status() << endl // 身份状态
			<< m_settime << endl // 存档设立时间
			<< m_name << endl // 名称
			<< m_career; // 职业
		return true;
	}
	cout << "\n\nFatalErro：无法生成通行证！\n\n";
	return false;
}
bool Save::OutputAdvance()
{
	using namespace std;
	const string advc = m_svdir + sv_AdvanceName();
	ofstream fout(advc);
	if (fout.is_open())
	{
		AcquireVrfcode();
		fout << m_vrfcode << endl // 效验码
			<< m_edittime << endl // 编辑时间
			<< m_moral << endl // 道德值
			<< m_3Q[0] << endl // IQ
			<< m_3Q[1] << endl // HQ
			<< m_3Q[2] << endl // EQ
			<< m_wealth; // 财富
		return true;
	}
	cout << "\n\nFatalErro：无法生成进度表！\n\n";
	return false;
}
bool Save::ReadSaveInfo(uint pos)
{
	using namespace std; using namespace ieTools;
	m_pos = pos;
	m_svdir = SaveDir() + "save" + to_string(pos) + "\\";
	//if (!savereg.bad_reg)
	{
		auto vClause = SplitString((*savereg.content_living)[pos - 1], SPLITPATTERN_SVREG());
		if (vClause[1] == to_string(eIllegal)) { return false; }
		if (ReadPassport() && ReadAdvance())
		{
			if (get_status() == eIllegal)
			{ 
				//OutputSaveInfo();
				UpdateLivingContent();
				return false;
			}
			if (to_string(get_num()) == vClause[0]) // 比对身份编号
			{
				string vrfcode = m_vrfcode;
				if (AcquireVrfcode() == vrfcode) // 比对效验码
				{
					return true;
				}
			}
		}
	}
	illegal();
	//OutputSaveInfo();
	UpdateLivingContent();
	return false;
}
bool Save::OutputSaveInfo()
{
	using namespace std; using namespace myTools; using namespace ieTools;
	if (!get_num() && get_status() == eIllegal)
	{
		auto vClause = SplitString((*savereg.content_living)[m_pos - 1], SPLITPATTERN_SVREG());
		set_num(atoi(vClause[0].c_str()));
		m_name = vClause[2];
		m_career = (atoi(vClause[3].c_str()));
		m_edittime = (atoi(vClause[4].c_str()));
	}
	UpdateLivingContent();
	m_svdir = SaveDir() + "save" + to_string(m_pos) + "\\";
	CreateDir(m_svdir);
	//if (savereg.OutputReg())
	{
		if (OutputPassport() && OutputAdvance())
		{
			return true;
		}
	}
	return false;
}
bool Save::CancelAccount(uint pos)
{
	using namespace std; using namespace ieTools; using namespace myTools;
	//if (pos) { m_pos = pos; }
	if (ReadSaveInfo(pos))
	{
		auto vClause = SplitString((*savereg.content_living)[m_pos - 1], SPLITPATTERN_SVREG());
		if (to_string(get_num()) == vClause[0]) // 比对身份编号
		{
			// 删除注册表条目并清空存档文件夹
			vector<string> content;
			for (int i = 1; i <= (*savereg.content_living).size(); i++)
			{
				if (i == m_pos)
				{
					cancel();
					string clause = FormRegClause();
					(*savereg.content_canceled).push_back(clause);
				}
				else
					content.push_back((*savereg.content_living)[i - 1]);
			}
			delete savereg.content_living; savereg.content_living = new vector<string>;
			*savereg.content_living = content;
			//if (savereg.OutputReg())
			{
				while (m_pos <= (*savereg.content_living).size())
				{
					string fromPass = SaveDir() + "save" + to_string(m_pos + 1) + "\\" + sv_PassportName();
					string fromAdva = SaveDir() + "save" + to_string(m_pos + 1) + "\\" + sv_AdvanceName();
					string toPass = SaveDir() + "save" + to_string(m_pos) + "\\" + sv_PassportName();
					string toAdva = SaveDir() + "save" + to_string(m_pos) + "\\" + sv_AdvanceName();
					myCopyFile(fromPass, toPass);
					myCopyFile(fromAdva, toAdva);
					m_pos++;
				}
				m_svdir = SaveDir() + "save" + to_string(m_pos) + "\\";
				DeleteDir(m_svdir);
				return true;
			}
		}
	}
	return false;
}

SaveReg::SaveReg()
{
	thelastnum = 0;
	GetClauseNum();
	//bad_reg = false;
}
SaveReg::~SaveReg()
{
	UpdatePlayerNum();
}
bool SaveReg::GetClauseNum()
{
	using namespace std; using namespace myTools; using namespace ieTools;
	string path = ini_PlayerPath();
	if (TestFileExistence(path) && TestFileContent(path))
	{
		ifstream fin(path);
		while (fin.peek() != EOF)
		{
			string line;
			getline(fin, line);
			decoder(line);
			auto vLine = SplitString(line, SPLITPATTERN_PLYR());
			if (vLine[0] == "PlayerNumber")
			{
				thelastnum = atoi(vLine[1].c_str());
				return true;
			}
		}
	}
	return false;
}
bool SaveReg::UpdatePlayerNum()
{
	using namespace std; using namespace myTools; using namespace ieTools;
	string path = ini_PlayerPath();
	if (TestFileExistence(path))
	{
		ifstream fin(path);
		vector<string> file;
		while (fin.peek() != EOF)
		{
			string line;
			getline(fin, line);
			decoder(line);
			auto vLine = SplitString(line, SPLITPATTERN_PLYR());
			if (vLine[0] == "PlayerNumber")
			{
				string newline = vLine[0] + SPLITPATTERN_PLYR() + to_string(thelastnum);
				file.push_back(newline);
			}
			else
				file.push_back(line);
		}
		fin.close();
		if (!TestFileContent(path))
		{
			string newline = "PlayerNumber" + SPLITPATTERN_PLYR() + to_string(thelastnum);
			file.push_back(newline);
		}
		ofstream fout(path);
		for (auto it = file.begin(); it != file.end(); it++)
		{
			fout << encoder(*it) << endl;
		}
		//thelastnum = 0;
	}
	return false;
}
bool SaveReg::ReadReg()
{
	using namespace std; using namespace myTools; using namespace ieTools;
	if (!content_living)
	{
		const string path = sv_RegisterPath();
		if (!TestFileExistence(path))
		{
			//bad_reg = true;
			return false;
		}
		content_living = new vector<string>;
		content_canceled = new vector<string>;
		ifstream fin(path);
		while (fin.peek() != EOF)
		{
			string clause;
			getline(fin, clause);
			decoder(clause);
			auto vClause = SplitString(clause, SPLITPATTERN_SVREG());
			if (vClause[1] == to_string(Player::eCancel))
			{
				//vClause = SplitString((*content_living)[(*content_living).size() - 1], SPLITPATTERN_SVREG());
				(*content_canceled).push_back(clause);
				getline(fin, clause);
			}
			else
			{
				(*content_living).push_back(clause);
			}
		}
		//bad_reg = false;
		}
	return true;
}

bool SaveReg::OutputReg()
{
	using namespace std; using namespace myTools;
	const string path = sv_RegisterPath();
	ofstream fout(path);
	if (fout.is_open())
	{
		for (auto it = (*content_living).begin(); it != (*content_living).end(); it++)
		{
			fout << encoder(*it) << endl;
		}
		for (auto it = (*content_canceled).begin(); it != (*content_canceled).end(); it++)
		{
			fout << encoder(*it) << endl;
		}
		//bad_reg = false;
		delete content_living;
		delete content_canceled;
		return true;
	}
	
	//bad_reg = true;
	return false;
	
}
int SaveReg::ShowLivingContent()
{
	using namespace std; using namespace ieTools; using namespace myTools;
	//if (!bad_reg)
	{
		//		0		1		2		3		4
		// 身份编号><身份状态><名称><职业编号><编辑时间
		for (int i = 0; i < content_living->size(); i++)
		{
			auto clause = SplitString((*content_living)[i], SPLITPATTERN_SVREG());
			auto time = SpanToTime(_atoi64(clause[4].c_str()));
			cout << i + 1 << ". " << GetCareerName(atoi(clause[3].c_str())) << clause[2]
				<< "于" << time.tm_year + 1900 << "年" << time.tm_mon + 1 << "月" << time.tm_mday << "日"
				<< time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec
				<< "保存";
			if (clause[1] == to_string(Player::eIllegal)) { cout << "（非法）"; }
			cout << endl;
		}
		int size = (*content_living).size();
		//delete content_living;
		//delete content_canceled;
		return size;
	}
	//else
		//return -1;
}
