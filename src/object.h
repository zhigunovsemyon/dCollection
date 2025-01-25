#pragma once
#include <istream>
#include <ostream>
#include <string_view>

class Object {
public:
	enum class exceptions {
		NOT_MATCHING_TYPES
	};

	/*Виртуальный деструктор*/
	virtual ~Object() = default;

	/*Возврат уникального идентификатора*/
	int id() const { return id_; }

	/*Возврат строки с типом объекта*/
	virtual std::string_view type() const = 0;

	/*Вывод содержимого в переданный поток*/
	virtual Object const & print(std::ostream & ost) const = 0;

	/*Перезапись данного файла*/
	virtual Object const & save(std::FILE *src) const = 0;

	/*Чтение из переданного потока*/
	virtual Object & read(std::istream & ist) = 0;

	/*Чтение из переданного файла*/
	virtual Object & read(std::FILE *src) = 0;

	/*Сравнение на равенство с другим объектом*/
	virtual bool equal(Object const &) const = 0;

	/*Добавление в текущий объект другого*/
	virtual Object & add(Object const &) = 0;

	/*Добавление в первый объект второго*/
	friend Object & operator+=(Object & a, Object const & b)
	{
		return a.add(b);
	}

	/*Сравнение на неравенство с другим объектом*/
	friend bool operator!=(Object const & a, Object const & b)
	{
		return !a.equal(b);
	}

	/*Сравнение на равенство с другим объектом*/
	friend bool operator==(Object const & a, Object const & b)
	{
		return a.equal(b);
	}

	/*Чтение содержимого из потока*/
	friend std::istream & operator>>(std::istream & ist, Object & obj)
	{
		obj.read(ist);
		return ist;
	}

	/*Вывод содержимого в поток*/
	friend std::ostream & operator<<(std::ostream & ost, Object const & obj)
	{
		obj.print(ost);
		return ost;
	}
	/* Функция сравнения. Возврат 1 если this > other, -1 если this < other,
	 * 0 при равенстве*/
	virtual int compare(Object const & other) const = 0;
	
	friend bool operator>(const Object &a, const Object &b)
	{
		return (a.compare(b) > 0) ? true : false;
	}

	friend bool operator<=(const Object &a, const Object &b)
	{
		return !(a > b);
	}

	friend bool operator<(const Object &a, const Object &b)
	{
		return (a.compare(b) < 0) ? true : false;
	}

	friend bool operator>=(const Object &a, const Object &b)
	{
		return !(a < b);
	}

protected:
	/*Сокрытый конструктор, инициализирующийся идентификатором*/
	Object() : id_{count_++} {}

private:
	static inline int count_; // Счётчик объектов
	int const id_;		  // Идентификатор класса
	
	virtual int rwSize() = 0; //Размер объекта при чтении или записи в бинарный файл
};
