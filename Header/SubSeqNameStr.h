#pragma once

struct SubSeqNameStr
{
	std::string TabName;
	std::string SubTabName;

	bool operator <( SubSeqNameStr right)
		const {
			int res = this->TabName.compare(right.TabName);
			if (res < 0)
				return true;
			else if (res > 0)
				return false;
			else
			{
				res = this->SubTabName.compare(right.SubTabName);
				if (res < 0)
					return true;
				else
					return false;
			}

			return true;
	}

	bool operator ==( SubSeqNameStr right)
		const {
			int res1 = this->TabName.compare(right.TabName);
			int res2 = this->SubTabName.compare(right.SubTabName);
			if ((res1 == 0) && (res2 ==0))
				return true;

			return false;
	}

};

typedef std::vector<SubSeqNameStr> sequenceNameListTypdef;