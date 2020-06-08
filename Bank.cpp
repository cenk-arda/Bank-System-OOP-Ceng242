#include "Bank.h"

/*private:
    std::string _bank_name;
    int _user_count;
    Account* _users;
*/

Bank::Bank(){
	_bank_name = "not_defined";
	_users = NULL;
	_user_count = 0;

}

Bank::Bank(std::string bank_name, Account* const users, int user_count){
	_bank_name = bank_name;
	_users = users;
/*	if(users==NULL) _users=NULL;
	else {
		int i;
		_users = new Account[user_count];
		for(i=0;i<user_count;i++){
			_users[i] = users[i];
		}
	}
//deep copy
*/
	_user_count= user_count;
	
}

Bank::~Bank(){
	if(_users!=NULL){
		int i;
		delete [] _users;		
	}
	int _user_count = 0;
}

Bank::Bank(const Bank& rhs){
	_user_count = rhs._user_count;
	_bank_name = rhs._bank_name;
	if(rhs._users ==NULL || _user_count==0){
		_users = NULL;
	}
	else{
		_users = new Account[_user_count];
		int i;
		for(i=0;i<_user_count;i++){
			_users[i] = rhs._users[i];
		}
	}	
}

Bank& Bank::operator+=(const Bank& rhs){
	/**
     * If both banks has a user with the same id, Transactions of these users will be merged in to the same Account
     * For example:
     * Bank1 has [1,2] id users
     * Bank2 has [2,3] id users
     * 
     * Bank1 after += operator will have [1,2,3] id users
     * User with id 2 will have its transactions histories merged
     * 
     * Transactions with of the users with the same id should be merged and updated
     * @param rhs Merged Bank
     * @return this Bank
     */
     if(this!=&rhs){
     	if (_users == NULL){
     		int i;
     		if(rhs._users==NULL|| rhs._user_count==0){
     			return *this;
			 }
     		_users = new Account[rhs._user_count];
     		_user_count = rhs._user_count;
     		for(i=0;i<rhs._user_count;i++){
     			_users[i]=rhs._users[i];
			 }
	        return *this;
		 }
		
		else if(rhs._users == NULL){
			return *this;
		}
		
		else{
			int i,j,k;
			int total = _user_count+rhs._user_count;
			for(i=0;i<_user_count;i++){
				for(j=0;j<rhs._user_count;j++){
					if(_users[i]==rhs._users[j]){
						total--;
					}
				}
			}
			
			Account *temp = new Account[total];
			k=0;
			for(i=0;i<_user_count;i++){
				bool check = true;
				for(j=0;j<rhs._user_count;j++){
				
						if(_users[i]==rhs._users[j]){
							_users[i]+=rhs._users[j];
							temp[k]=(_users[i]);
							k++;
							check = false;
							break;
						}
				}
				if (check){
					temp[k] = _users[i];
					k++;
				}
				
			}
			
			if(k<total){
				for(i=0;i<rhs._user_count;i++){
					bool check = true;
					for(j=0;j<_user_count;j++){
						if(rhs._users[i]==_users[j]){
							check = false;
							break;
						}
					}
					if(check){
						temp[k]= rhs._users[i];
						k++; 
					}
				}
			}					
		 _users = temp;	
	     _user_count = total;
        }	
	 }
	return *this;
}



Bank& Bank::operator+=(const Account& new_acc){
	 /*
     * Add a new account to Bank
     * 
     * If the newly added user already exists in this Bank merge their Transactions
     * 
     * @param new_acc new account to add to bank
     * @return this Bank
     */
     /*private:
     std::string _bank_name;
     int _user_count;
     Account* _users;
     */
 
	 if(_users==NULL){
	 	 
     	_users =new Account[1];
     	_users[0] = new_acc;
     	_user_count = 1;
     	return *this;
	 }
	 else{
	 	int i;
	 	for(i=0;i<_user_count;i++){
	 		if(_users[i]==new_acc){
	 			_users[i]+= new_acc;
	 			return *this;
			 }
		}
		int a = _user_count+1;
		Account *temp = new Account[a];
		
		for(i=0;i<_user_count;i++){
			temp[i]=_users[i];
		} 
		temp[i] = new_acc;
	    _users = temp;
		_user_count++;
	 	return *this;
	 }
    
}

Account& Bank::operator[](int account_id){
	int i;
	if(_users!=NULL){
		for(i=0;i<_user_count;i++){
			if(_users[i]==account_id){
				return _users[i];
			}
		}
		return _users[i];
	}
}

std::ostream& operator<<(std::ostream& os, const Bank& bank){
    /**
     * Stream overload.
     * all the accounts will be between 01-01-2019 and 31-12-2019
     * What to stream
     * bank_name"tab"number of users who are eligible for a loan"tab"total balance of the bank
     * 
     * A user is safe for a loan if and only if that user did not have any negative balance for 2 or more consecutive months
     * For example, let's say our bank named as "banana" has two users
     * 
     * User A's balance for each month is as given
     * 
     * January - 0
     * February - 0
     * March - 100
     * April - -20
     * May - -30
     * June - 40
     * July - 60
     * August - 0
     * September - 0
     * October - 0
     * November - 0
     * December - 0
     * 
     * This user is not eligible because in April and May his/her balance was negative(consecutive)
     * You still have to add 150 to the total balance of the bank
     * User B's balance for each month is as given
     * 
     * January - 0
     * February - 0
     * March - 100
     * April - -20
     * May - 40
     * June - -30
     * July - 60
     * August - 0
     * September - 0
     * October - 0
     * November - 0
     * December - 0
     * 
     * This user is eligible because negative balances were not consecutive
     * You will also add 150 to the total balance of the bank
     * 
     * your output will be as
     * banana   1   300
     */ 
     
     
     int i,j,k;
     double total_balance = 0;
     int count_of_eligible = 0;
     for(i=0;i<bank._user_count;i++){
     	double *balance_list = new double[11]{0};
		 for(j=0;j<11;j++){
			 struct tm start;
		     start.tm_isdst=0;
		     start.tm_year = 119;
		     start.tm_mon = j;
		     start.tm_mday = 1;
		     start.tm_hour = 0;
		     start.tm_min = 0;
		     start.tm_sec = 0;	
		     
			 struct tm end;
		     if(j==10){
		     	 end.tm_isdst=0;
			     end.tm_year = 119;
			     end.tm_mon = j+1;
			     end.tm_mday = 31;
			     end.tm_hour =23;
			     end.tm_min = 59;
			     end.tm_sec = 59;	
		     
			 }
		    else{
		    	 end.tm_isdst=0;
			     end.tm_year = 119;
			     end.tm_mon = j+1;
			     end.tm_mday = 1;
			     end.tm_hour = 0;
			     end.tm_min = 0;
			     end.tm_sec = 0;	
			} 

		     time_t start_date = mktime(&start);
		     time_t end_date = mktime(&end);		     
			 balance_list[j] = bank._users[i].balance(start_date,end_date);
	     }
	     total_balance = total_balance + bank._users[i].balance() ; 
	    
		bool eligible= true;
	    for(k=0;k<10;k++){
	    	if(balance_list[k]<0&&balance_list[k+1]<0){
	    		eligible = false;
	    		break;
			}
		}
		
		if(eligible){
			count_of_eligible++;
		}
		
     	delete [] balance_list;	
	 }
	 
     os<<bank._bank_name<<"\t"<<count_of_eligible<<"\t"<<total_balance<<"\n";
     return os;
     	
}
