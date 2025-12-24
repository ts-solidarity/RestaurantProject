#include <iostream>
#include <iomanip>
#include "User.h"

User::User(int userId, const std::string& userName, const std::string& userEmail)
{
	m_UserId = userId;
	m_UserName = userName;
	m_UserEmail = userEmail;
}

void User::DisplayInfo() const {
	std::cout << std::left << std::setw(15) << "User ID:" << m_UserId << "\n"
		<< std::setw(15) << "Name:" << m_UserName << "\n"
		<< std::setw(15) << "Email:" << m_UserEmail << std::endl;
}

int User::GetUserId() const
{
	return m_UserId;
}

std::string User::GetUserName() const
{
	return m_UserName;
}

std::string User::GetUserEmail() const
{
	return m_UserEmail;
}

void User::SetUserId(int userId)
{
	m_UserId = userId;
}

void User::SetUserName(const std::string& userName)
{
	m_UserName = userName;
}

void User::SetUserEmail(const std::string& userEmail)
{
	m_UserEmail = userEmail;
}
