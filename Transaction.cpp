#include "Transaction.h"

Transaction::Transaction(){
	_amount = -1;
	_date = -1;
	//std::cout<<"A TRANSACTION HAS BEEN CREATED"<<"\n";
}

Transaction::Transaction(double amount, time_t date){
	_amount = amount;
	_date = date;
}		

Transaction::Transaction(const Transaction& rhs){
	_amount = rhs._amount;
	_date = rhs._date;
}

bool Transaction::operator<(const Transaction& rhs) const{
	return (_date<rhs._date);
}

bool Transaction::operator>(const Transaction& rhs) const{
	return (_date>rhs._date);
}

bool Transaction::operator<(const time_t date) const{
	return _date<date;
} 

bool Transaction::operator>(const time_t date) const{
	return _date>date;
} 

double Transaction::operator+(const Transaction &rhs){
	return _amount+rhs._amount;
}

double Transaction::operator+(const double add){
	return _amount+add;
}

Transaction& Transaction::operator=(const Transaction& rhs){
	if(this!=&rhs){
	_amount = rhs._amount;
	_date = rhs._date;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Transaction& transaction){
	/* What to stream:
     * Transaction amount"tab-tab"hour:minute:second-day/month/year(in localtime)   */
	os << transaction._amount <<"\t-\t"<<(localtime(&transaction._date))->tm_hour<<":"<<(localtime(&transaction._date))->tm_min<<":"<<localtime(&transaction._date)->tm_sec<<"-"<<localtime(&transaction._date)->tm_mday<<"/"<<localtime(&transaction._date)->tm_mon+1<<"/"<<localtime(&transaction._date)->tm_year+1900<<"\n";
	return os;
}



	

