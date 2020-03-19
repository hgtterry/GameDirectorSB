#pragma once
class GD_spdlog
{
public:
	GD_spdlog();
	~GD_spdlog();

	void stdout_example(int Num,bool Kill);

	void GD_spdlog::Init();

	bool ConsoleActive;
};

