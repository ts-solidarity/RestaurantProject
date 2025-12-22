#pragma once
#include <string>


class User
{

public:

	User(int userId, const std::string& userName, const std::string& userEmail);
	virtual ~User() = default;

	virtual void DisplayInfo() const;

	int GetUserId() const;
	std::string GetUserName() const;
	std::string GetUserEmail() const;

	void SetUserId(int userId);
	void SetUserName(const std::string& userName);
	void SetUserEmail(const std::string& userEmail);


private:

	int m_UserId;
	std::string m_UserName;
	std::string m_UserEmail;

};
