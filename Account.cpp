#include "Account.h"
/*private:
    int _id;
    Transaction** _activity;
    int* _monthly_activity_frequency;
*/
Account::Account(){
	_id = -1;
	_activity = NULL;
	_monthly_activity_frequency = NULL;	

}

Account::Account(int id, Transaction** const activity, int* monthly_activity_frequency){
	_id = id;
	_activity = new Transaction* [12];
	_monthly_activity_frequency = new int[12];
	bool check;
	int i; int j; int k;
	for(i=0;i<12;i++){
		if (monthly_activity_frequency[i]==0){
			_activity[i] = NULL;
			_monthly_activity_frequency[i] = 0;
		}
		else {
			int length = monthly_activity_frequency[i];
			_monthly_activity_frequency[i] = length;
			_activity[i] = new Transaction[length];
			for(j=0; j<length; j++){
				_activity[i][j] = activity[i][j]; 
			}
		}		
    }
    
    for(i=0; i<12; i++){
    	if (monthly_activity_frequency[i]==0){
    		continue;
		}
		for(j=0; j<monthly_activity_frequency[i]-1; j++){
			check = false;
			for(k=0;k<monthly_activity_frequency[i]-1-j; k++){
				if(_activity[i][k]>_activity[i][k+1]){
					Transaction temp = _activity[i][k];
					_activity[i][k] = _activity[i][k+1];
					_activity[i][k+1] = temp;
					check = true;
				}
			}
		if(check==false) break;	
		}
	}

}

Account::~Account(){
	int i,j;
	if(_activity!=NULL){
		for(i =0; i<12; i++){
			if(_activity[i]!=NULL) delete [] _activity[i];
	}
	delete [] _activity;	
	}

	if(_monthly_activity_frequency!=NULL)
	delete [] _monthly_activity_frequency;
	
}

Account::Account(const Account& rhs){
		bool check;
		_id = rhs._id;
		int i;int j; int k;
		_activity = new Transaction*[12];
		_monthly_activity_frequency = new int[12];
		for(i=0;i<12;i++){
			if (rhs._monthly_activity_frequency[i]==0){
				_activity[i] = NULL;
				_monthly_activity_frequency[i] = 0;
			}
			else {
				int length = rhs._monthly_activity_frequency[i];
				_monthly_activity_frequency[i] = length;
				_activity[i] = new Transaction[length];
				for(j=0; j<length; j++){
					_activity[i][j] = rhs._activity[i][j]; 
				}
			}		
	    }
	    for(i=0; i<12; i++){
			if (rhs._monthly_activity_frequency[i]==0){
				continue;
			}
			for(j=0; j<rhs._monthly_activity_frequency[i]-1; j++){
				check = false;
				for(k=0;k<rhs._monthly_activity_frequency[i]-1-j; k++){
					if(_activity[i][k]>_activity[i][k+1]){
						Transaction temp = _activity[i][k];
						_activity[i][k] = _activity[i][k+1];
						_activity[i][k+1] = temp;
						check = true;
					}
				}
			if(check==false) break;	
			}
	    }	
	  
}

Account::Account(const Account& rhs, time_t start_date, time_t end_date){

	int i,j,k;
	_id = rhs._id;	
	_activity = new Transaction*[12];
	_monthly_activity_frequency = new int[12]; //initiliaze 0?	
	for(i=0;i<12;i++) _monthly_activity_frequency[i] = 0;
	
	for(i=0;i<12;i++){
		if (rhs._monthly_activity_frequency[i]==0 || rhs._activity[i]==NULL) {
			_activity[i] = NULL;
			_monthly_activity_frequency[i] = 0;
		}
		else {
			for(j=0;j<rhs._monthly_activity_frequency[i];j++){
				if(rhs._activity[i][j]>start_date && rhs._activity[i][j]<end_date){
					_monthly_activity_frequency[i]++;
				}
			}
		}			
	}
		
	for(i=0;i<12;i++){
		if(_monthly_activity_frequency[i]==0||rhs._monthly_activity_frequency[i]==0){
			_activity[i]=NULL;
		}
		else{
			
			_activity[i]= new Transaction[_monthly_activity_frequency[i]]; 
			for(j=0,k=0;j<rhs._monthly_activity_frequency[i];j++){
				if(rhs._activity[i][j]>start_date && rhs._activity[i][j]<end_date){
					 _activity[i][k]=rhs._activity[i][j];
					 k++; 
				}
			}
			
		}
	}

}

Account::Account(Account&& rhs){
	 /**
     * Move constructor
     * 
     * @param rhs Account which you will move the resources from
     */
     
	_id = rhs._id;
	_activity = rhs._activity;
	_monthly_activity_frequency = rhs._monthly_activity_frequency;
	
	rhs._id = 0;
	rhs._activity = NULL;
	rhs._monthly_activity_frequency = NULL;
 
}

Account& Account:: operator=(Account&& rhs){
	if(_activity!=NULL){
		int i;
		for(i=0;i<12;i++){
			if(_activity[i]!=NULL)delete [] _activity[i];
		}
		delete [] _activity;
	}	
	_activity = rhs._activity;
    if(_monthly_activity_frequency!=NULL) delete [] _monthly_activity_frequency; 
    _monthly_activity_frequency = rhs._monthly_activity_frequency;
    rhs._monthly_activity_frequency = NULL;
    rhs._activity = NULL;
	_id = rhs._id;
	rhs._id = 0;
	return *this;			
		
}

Account& Account::operator=(const Account& rhs){
if(this!=&rhs){
	int i,j,k;
	bool check;
	_id = rhs._id;
	if(_activity!=NULL){
		for(i=0;i<12;i++){
			if(_activity[i]!=NULL )delete [] _activity[i];
		}
		delete [] _activity;
	}
	if(_monthly_activity_frequency!=NULL){
		delete [] _monthly_activity_frequency;
	}
	
	_activity = new Transaction*[12];
	_monthly_activity_frequency = new int[12];
	
	for(i=0;i<12;i++){
		if (rhs._activity[i]==NULL){
			_activity[i] = NULL;
			_monthly_activity_frequency[i] = 0;
		}
		else {
			int length = rhs._monthly_activity_frequency[i];
			_monthly_activity_frequency[i] = length;
			_activity[i] = new Transaction[length];
			for(j=0; j<length; j++){
				_activity[i][j] = rhs._activity[i][j]; 
			}
		}		
    }
    for(i=0; i<12; i++){
		if (_activity[i]==NULL){
			continue;
		}
		for(j=0; j<_monthly_activity_frequency[i]-1; j++){
			check = false;
			for(k=0;k<_monthly_activity_frequency[i]-1-j; k++){
				if(_activity[i][k]>_activity[i][k+1]){
					Transaction temp = _activity[i][k];
					_activity[i][k] = _activity[i][k+1];
					_activity[i][k+1] = temp;
					check = true;
				}
			}
		if(check==false) break;	
		}
    }
}
   	return *this; 
}

bool Account::operator==(const Account& rhs) const{
	return(_id==rhs._id);
}
bool Account::operator==(int id) const{
	return(_id==id);
}

Account& Account::operator+=(const Account& rhs){
/**
 * sum and equal operator
 * Add Transactions of two Accounts
 * You have to add transactions in correct places in your _activity array
 * Note: Remember that _activity[0] is always January and _activity[11] is always December
 * (This information also holds for every other month)
 * 
 * You can have Transactions with the same date
 * 
 * @param rhs Account which take new Transactions from
 * @return this Account after adding new Transactions
 */
 /*private:
 int _id;
 Transaction** _activity;
 int* _monthly_activity_frequency;
 */
	 Transaction** temp = new Transaction*[12];
	 int *total_frequency = new int[12];
	 int i,j,k;
	 bool check;
	 for(i=0;i<12;i++){
	 	total_frequency[i] = _monthly_activity_frequency[i] + rhs._monthly_activity_frequency[i]; 
	 }
	 for(i=0;i<12;i++){
	 	if(total_frequency[i]==0){
	 		temp[i]=NULL;
		 }
		else{
			temp[i] = new Transaction[total_frequency[i]];
			int t,r;
			for(t=0; t<_monthly_activity_frequency[i]; t++){
				temp[i][t] = _activity[i][t];  
			}
			for(r=0;r<rhs._monthly_activity_frequency[i];r++){
				temp[i][r+t] = rhs._activity[i][r];
			}
		}	
	 }
	 for(i=0; i<12; i++){
		if (total_frequency[i]==0){
			continue;
		}
		for(j=0; j<total_frequency[i]-1; j++){
			check = false;
			for(k=0;k<total_frequency[i]-1-j; k++){
				if(temp[i][k]>temp[i][k+1]){
					Transaction tmp = temp[i][k];
					temp[i][k] = temp[i][k+1];
					temp[i][k+1] = tmp;
					check = true;
				}
			}
			if(check==false) break;	
		}
	 }
	 if(_activity!=NULL){
	  for(i=0;i<12;i++){
	 	if(_activity[i]!=NULL)delete [] _activity[i];
	 }
	 delete [] _activity;
	 }
	
	 if(_monthly_activity_frequency!=NULL) delete [] _monthly_activity_frequency;
	 
	 _activity = temp;
	 _monthly_activity_frequency = total_frequency;
	 return *this;
}

double Account:: balance(){
	 /**
     * How much money Account has(Sum of Transaction amounts)
     *
     * 
     * @return total amount of the money of the account
     */
     int i,j;
     double balance = 0;
     for(i=0;i<12;i++){
     	if(_activity[i]==NULL){
     		continue;
		 }
		for(j=0;j<_monthly_activity_frequency[i];j++){
			balance = _activity[i][j] + balance; 
		}
	 }
	 return balance;
}


   
double Account:: balance(time_t end_date){

 /**
     * How much money Account has at the end of given date
     * 
     * Given date will not be included.
     * @param end_date You will count the amounts until this given date(not inclusive)
     * @return Total amount the Account has until given date
     */
     int i,j;
     double balance = 0;
     
    for(i=0;i<12;i++){
     	if(_activity[i]==NULL){
     		continue;
		}
        for(j=0;j<_monthly_activity_frequency[i];j++){
		    if(_activity[i][j]<end_date){
				balance = _activity[i][j] + balance; 
			}
		}
	 }
	 
	 return balance;
	   
}

double Account:: balance(time_t start_date, time_t end_date){
     int i,j;
     double balance = 0;
     
    for(i=0;i<12;i++){
     	if(_activity[i]==NULL){
     		continue;
		}
        for(j=0;j<_monthly_activity_frequency[i];j++){
		    if(_activity[i][j]<end_date && _activity[i][j]>start_date){
				balance = _activity[i][j] + balance; 
			}
		}
	 }
	 return balance;
}

    
std::ostream& operator<<(std::ostream& os, const Account& account){
	/**
     * Stream overload.
     * 
     * 
     * 
     * What to stream
     * Id of the user
     * Earliest Transaction amount"tab"-"tab"hour:minute:second-day/month/year(in localtime)
     * Second earliest Transaction amount"tab"-"tab"hour:minute:second-day/month/year(in localtime)
     * ...
     * Latest Transaction amount"tab-tab"hour:minute:second-day/month/year(in localtime)
     * 
     * Note: _activity array will only contain dates from January 2019 to December 2019
     * Note: Transactions should be in order by date
     * Note: either of _monthly_activity_frequency or _activity is nullptr
     * you will just stream
     * -1
     * @param os Stream to be used.
     * @param Account to be streamed.
     * @return the current Stream
     */
	if(account._activity==NULL || account._monthly_activity_frequency==NULL ){
		os<<-1<<"\n";
		return os;
	}
	else{
		os<<account._id<<"\n";
		int i,j;
		for(i=0;i<12;i++){
		
			for(j=0;j<account._monthly_activity_frequency[i];j++){
				if(account._activity[i]!=NULL){
				os<<account._activity[i][j];
				}
				
			}
			
		}
		return os;
	}
}





