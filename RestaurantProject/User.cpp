#include <iostream>
#include "User.h"

User::User(int userId, const std::string& userName, const std::string& userEmail)
{
	m_UserId = userId;
	m_UserName = userName;
	m_UserEmail = userEmail;
}

void User::DisplayInfo() const
{
	std::cout << "User Id: " << m_UserId << std::endl;
	std::cout << "User Name: " << m_UserName << std::endl;
	std::cout << "User Email: " << m_UserEmail << std::endl;
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
