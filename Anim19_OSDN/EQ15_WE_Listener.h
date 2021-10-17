#pragma once
class EQ15_WE_Listener
{
public:
	EQ15_WE_Listener();
	~EQ15_WE_Listener();

	bool WE_RenderingQueued(const FrameEvent& evt);
};

