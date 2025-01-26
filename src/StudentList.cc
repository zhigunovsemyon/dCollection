#include "StudentList.h"
#include <ostream>

StudentList & StudentList::add_(Student const & A)
{
	MaxNameWidth_ = static_cast<int>(std::max(
		static_cast<size_t>(MaxNameWidth_.get()), A.Name.length()));
	MaxSurnameWidth_ = static_cast<int>(
		std::max(static_cast<size_t>(MaxSurnameWidth_.get()),
			 A.Surname.length()));
	MaxPatronimWidth_ = static_cast<int>(
		std::max(static_cast<size_t>(MaxPatronimWidth_.get()),
			 A.Patronim.length()));

	list_.push_back(A);
	return *this;
}

StudentList & StudentList::enter(std::istream & ist)
{
	Student tmp{};
	ist >> tmp.N >> tmp.Surname >> tmp.Name >> tmp.Patronim;
	for (auto & mark : tmp.Marks)
		ist >> mark;

	if (ist.good()) {
		tmp.AvgMark = AvgMark_(tmp.Marks);
		add_(tmp);
	}

	return *this;
}

/*Вывод без форматирования*/
std::ostream & operator<<(std::ostream & ost, StudentList const & list)
{
	for (auto & rec : list.list_) {
		ost << rec.N << ' ' << rec.Surname << ' ' << rec.Name;
		ost << ' ' << rec.Patronim << ' ' << rec.AvgMark << ' ';
		for (auto & mark : rec.Marks)
			ost << mark << ' ';
		ost << '\n';
	}

	return ost;
}

/*Чтение из текстового потока*/
std::istream & operator>>(std::istream & ist, StudentList & list)
{
	do {
		StudentList::Student tmp{};
		ist >> tmp.N >> tmp.Surname >> tmp.Name;
		ist >> tmp.Patronim >> tmp.AvgMark;
		if (tmp.AvgMark.get() < 1.0 || tmp.AvgMark.get() > 5.0)
			return ist;

		for (auto & mark : tmp.Marks) {
			ist >> mark;
			if (mark.get() > 5 || mark.get() < 1)
				return ist;
		}

		if (ist.good()) {
			list.add_(tmp);
		}
	} while (ist.good());

	return ist;
}

int StudentList::FindStudentByN(int n) const
{
	int i{};
	for (auto & rec : list_) {
		if (rec.N.get() == n)
			return i;
		/*else*/ ++i;
	}
	return -1;
}

/*Поиск записи с соответствующим именем*/
int StudentList::FindStudentByName(String const & str) const
{
	int i{};
	for (auto & rec : list_) {
		if (rec.Name == str)
			return i;
		/*else*/ ++i;
	}
	return -1;
}

/*Поиск записи с соответствующим номером*/
int StudentList::FindStudentByPatronim(String const & str) const
{
	int i{};
	for (auto & rec : list_) {
		if (rec.Patronim == str)
			return i;
		/*else*/ ++i;
	}
	return -1;
}

/*Поиск записи с соответствующей фамилией*/
int StudentList::FindStudentBySurname(String const & str) const
{
	int i{};
	for (auto & rec : list_) {
		if (rec.Surname == str)
			return i;
		/*else*/ ++i;
	}
	return -1;
}

/*Удаление записи с соответствующим номером*/
bool StudentList::DeleteStudentWithN(int n)
{
	auto i{FindStudentByN(n)};
	if (i < 0)
		return false;
	list_.erase(list_.begin() + i);
	return true;
}

/*Удаление записи с соответствующим именем*/
bool StudentList::DeleteStudentWithName(String const & str)
{
	auto i{FindStudentByName(str)};
	if (i < 0)
		return false;
	list_.erase(list_.begin() + i);
	return true;
}

/*Удаление записи с соответствующим номером*/
bool StudentList::DeleteStudentWithPatronim(String const & str)
{
	auto i{FindStudentByPatronim(str)};
	if (i < 0)
		return false;
	list_.erase(list_.begin() + i);
	return true;
}

/*Удаление записи с соответствующей фамилией*/
bool StudentList::DeleteStudentWithSurname(String const & str)
{
	auto i{FindStudentBySurname(str)};
	if (i < 0)
		return false;
	list_.erase(list_.begin() + i);
	return true;
}

/*Повторный ввод записи с соответствующим номером*/
bool StudentList::ReenterStudentWithN(std::istream & ist, int n)
{
	auto i{FindStudentByN(n)};
	if (i < 0)
		return false;

	StudentList::Student tmp{};
	ist >> tmp.N >> tmp.Surname >> tmp.Name >> tmp.Patronim;
	for (auto & mark : tmp.Marks)
		ist >> mark;

	if (ist.bad())
		return false;

	tmp.AvgMark = AvgMark_(tmp.Marks);
	std::swap(tmp, *(list_.data() + i));
	return true;
}

/*Повторный ввод записи с соответствующим именем*/
bool StudentList::ReenterStudentWithName(std::istream & ist, String const & str)
{
	auto i{FindStudentByName(str)};
	if (i < 0)
		return false;

	StudentList::Student tmp{};
	ist >> tmp.N >> tmp.Surname >> tmp.Name >> tmp.Patronim;
	for (auto & mark : tmp.Marks)
		ist >> mark;

	if (ist.bad())
		return false;


	MaxNameWidth_= static_cast<int>(
		std::max(static_cast<size_t>(MaxNameWidth_.get()),
			 tmp.Name.length()));

	tmp.AvgMark = AvgMark_(tmp.Marks);
	std::swap(tmp, *(list_.data() + i));
	return true;
}

/*Повторный ввод записи с соответствующим номером*/
bool StudentList::ReenterStudentWithPatronim(std::istream & ist,
					     String const & str)
{
	auto i{FindStudentByPatronim(str)};
	if (i < 0)
		return false;

	StudentList::Student tmp{};
	ist >> tmp.N >> tmp.Surname >> tmp.Name >> tmp.Patronim;
	for (auto & mark : tmp.Marks)
		ist >> mark;

	if (ist.bad())
		return false;

	MaxPatronimWidth_ = static_cast<int>(
		std::max(static_cast<size_t>(MaxPatronimWidth_.get()),
			 tmp.Patronim.length()));

	tmp.AvgMark = AvgMark_(tmp.Marks);
	std::swap(tmp, *(list_.data() + i));
	return true;
}

/*Повторный ввод записи с соответствующей фамилией*/
bool StudentList::ReenterStudentWithSurname(std::istream & ist,
					    String const & str)
{
	auto i{FindStudentBySurname(str)};
	if (i < 0)
		return false;

	StudentList::Student tmp{};
	ist >> tmp.N >> tmp.Surname >> tmp.Name >> tmp.Patronim;
	for (auto & mark : tmp.Marks)
		ist >> mark;

	if (ist.bad())
		return false;

	MaxSurnameWidth_= static_cast<int>(
		std::max(static_cast<size_t>(MaxSurnameWidth_.get()),
			 tmp.Surname.length()));

	tmp.AvgMark = AvgMark_(tmp.Marks);
	std::swap(tmp, *(list_.data() + i));
	return true;
}

static void PrintCharNTimes(std::ostream & ost, char const * c, int n)
{
	for (auto i{0}; i < n; ++i)
		ost << c;
}

static void
PrintWithSpaces(std::ostream & ost, String const & str, int TotalWidth)
{
	ost << str;
	PrintCharNTimes(ost, " ", TotalWidth - static_cast<int>(str.length()));
}

void StudentList::printHead(std::ostream & ost) const
{
	/*Шапка таблицы 1*/
	ost << "┏━━━┯";
	PrintCharNTimes(ost, "━", MaxSurnameWidth_.get());
	ost << "┯";
	PrintCharNTimes(ost, "━", MaxNameWidth_.get());
	ost << "┯";
	PrintCharNTimes(ost, "━", MaxPatronimWidth_.get());
	ost << "┯";
	PrintCharNTimes(ost, "━", 3);
	ost << "┯";
	PrintCharNTimes(ost, "━", (mcount * 2) - 1);
	ost << "┓\n";

	/*Шапка таблицы 2*/
	ost << "┃№  │";
	PrintWithSpaces(ost, "Фамилия", MaxSurnameWidth_.get());
	ost << "│";
	PrintWithSpaces(ost, "Имя", MaxNameWidth_.get());
	ost << "│";
	PrintWithSpaces(ost, "Отчество", MaxPatronimWidth_.get());
	ost << "│AVG│1 2 3 4 5┃\n";

	ost << "┣━━━┿";
	PrintCharNTimes(ost, "━", MaxSurnameWidth_.get());
	ost << "┿";
	PrintCharNTimes(ost, "━", MaxNameWidth_.get());
	ost << "┿";
	PrintCharNTimes(ost, "━", MaxPatronimWidth_.get());
	ost << "┿";
	PrintCharNTimes(ost, "━", 3);
	ost << "┿";
	PrintCharNTimes(ost, "━", (mcount * 2) - 1);
	ost << "┫\n";
}

void StudentList::printSeparator(std::ostream & ost) const
{
	ost << "┠───┼";
	PrintCharNTimes(ost, "─", MaxSurnameWidth_.get());
	ost << "┼";
	PrintCharNTimes(ost, "─", MaxNameWidth_.get());
	ost << "┼";
	PrintCharNTimes(ost, "─", MaxPatronimWidth_.get());
	ost << "┼";
	PrintCharNTimes(ost, "─", 3);
	ost << "┼";
	PrintCharNTimes(ost, "─", (mcount * 2) - 1);
	ost << "┨\n";
}

void StudentList::printEntry(std::ostream & ost, Student const & rec) const
{
	ost << "┃" << rec.N;
	if (rec.N.get() < 100)
		ost << ' ';
	if (rec.N.get() < 10)
		ost << ' ';
	ost << "│";

	PrintWithSpaces(ost, rec.Surname, MaxSurnameWidth_.get());
	ost << "│";
	PrintWithSpaces(ost, rec.Name, MaxNameWidth_.get());
	ost << "│";
	PrintWithSpaces(ost, rec.Patronim, MaxPatronimWidth_.get());
	ost.precision(3);
	ost << "│" << rec.AvgMark << "│";
	for (auto i{0lu};;) {
		ost << rec.Marks[i++];
		if (i == rec.Marks.size())
			break;
		ost << ' ';
	}
	ost << "┃\n";
}

void StudentList::printFooter(std::ostream & ost) const
{
	ost << "┗━━━┷";
	PrintCharNTimes(ost, "━", MaxSurnameWidth_.get());
	ost << "┷";
	PrintCharNTimes(ost, "━", MaxNameWidth_.get());
	ost << "┷";
	PrintCharNTimes(ost, "━", MaxPatronimWidth_.get());
	ost << "┷";
	PrintCharNTimes(ost, "━", 3);
	ost << "┷";
	PrintCharNTimes(ost, "━", (mcount * 2) - 1);
	ost << "┛\n";
}
