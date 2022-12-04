long long getCurrentTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
long long timelast,timenow,timegap;