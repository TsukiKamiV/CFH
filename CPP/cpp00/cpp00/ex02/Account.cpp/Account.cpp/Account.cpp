//
//  main.cpp
//  Account.cpp
//
//  Created by Luyao Xu on 02/10/2025.
//

#include <iostream>
#include <ctime>
#include "Account.hpp"

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit)
:	_accountIndex(_nbAccounts),
	_amount(initial_deposit),
	_nbDeposits(0),
	_nbWithdrawals(0)
{
	_nbAccounts += 1;
	_totalAmount += initial_deposit;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
			  << ";amount:" << _amount
	<< ";created" << std::endl;
}

Account::~Account(){
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
			  << ";amount:" << _amount
	<< ";closed" << std::endl;
}

void	Account::_displayTimestamp() {
	time_t	now = time(NULL);
	struct tm* tm_info = localtime(&now);
	
	std::cout << "["
	<< (tm_info->tm_year + 1900)
	<< (tm_info->tm_mon + 1 < 10 ? "0" : "") << tm_info->tm_mon + 1
	<< (tm_info->tm_mday < 10 ? "0" : "") << tm_info->tm_mday
	<< "_"
	<< (tm_info->tm_hour < 10 ? "0" : "") << tm_info->tm_hour
	<< (tm_info->tm_min < 10 ? "0" : "") << tm_info->tm_min
	<< (tm_info->tm_sec < 10 ? "0" : "") << tm_info->tm_sec << "] ";
}

void	Account::displayAccountsInfos( void ) {
	Account::_displayTimestamp();
	std::cout << "accounts:" << Account::_nbAccounts
			  << ";total:" << Account::_totalAmount
			  << ";deposits:" << Account::_totalNbDeposits
	<< ";withdrawals:" << Account::_totalNbWithdrawals << std::endl;
	
}

void	Account::displayStatus() const {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
			  << ";amount:" << _amount
			  << ";deposits:" << _nbDeposits
	<< ";withdrawals:" <<  _nbWithdrawals << std::endl;
}

void	Account::makeDeposit( int deposit ) {
	int	previous = _amount;
	
	_amount += deposit;
	_nbDeposits += 1;
	
	_totalAmount += deposit;
	_totalNbDeposits += 1;
	
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
			  << ";p_amount:" << previous
			  << ";deposit:" << deposit
			  << ";amount:" << _amount
	<< ";nb_deposits:" << _nbDeposits << std::endl;
}

bool	Account::makeWithdrawal( int withdrawal ){
	
	bool	is_enough;
	int		tmp_amount = _amount;
	int		previous = _amount;
	
	tmp_amount -= withdrawal;
	if ( tmp_amount >= 0) {
		_amount = tmp_amount;
		is_enough = true;
		_nbWithdrawals += 1;
		
		_totalAmount -= withdrawal;
		_totalNbWithdrawals += 1;
		
		_displayTimestamp();
		std::cout << "index:" << _accountIndex
		<< ";p_amount:" << previous
		<< ";withdrawal:" << withdrawal
		<< ";amount:" << _amount
		<< ";nb_withdrawals:" << _nbWithdrawals << std::endl;
	}
	else {
		is_enough = false;
		_displayTimestamp();
		std::cout << "index:" << _accountIndex
				  << ";p_amount:" << previous
		<< ";withdrawal:refused" << std::endl;
	}
	return is_enough;
}

int	Account::getNbAccounts( void ){
	return _nbAccounts;}

int	Account::getTotalAmount( void ){
	return _totalAmount;}

int	Account::getNbDeposits( void ){
	return _totalNbDeposits;}

int	Account::getNbWithdrawals( void ){
	return _totalNbWithdrawals;}

int	Account::checkAmount( void ) const  {
	return _amount;}
