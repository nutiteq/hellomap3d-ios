#ifndef LOG_H_
#define LOG_H_

#include <atomic>
#include <mutex>
#include <string>

namespace Nuti {

/**
 * A diagnostic log for various SDK events.
 */
class Log {
public:
	static void Fatal(const char* text, ...);
	static void Error(const char* text, ...);
	static void Warn(const char* text, ...);
	static void Info(const char* text, ...);
	static void Debug(const char* text, ...);

	/**
	 * Enables or disables writing error messages to the log.
	 * @param showError If true, then error messages will be written to the log.
	 */
	static void SetShowError(bool showError);
	/**
	 * Enables or disables writing warning messages to the log.
	 * @param showWarn If true, then warning messages will be written to the log.
	 */
	static void SetShowWarn(bool showWarn);
	/**
	 * Enables or disables writing info messages to the log.
	 * @param showInfo If true, then info messages will be written to the log.
	 */
	static void SetShowInfo(bool showInfo);
	/**
	 * Enables or disables writing internal debug messages to the log.
	 * @param showDebug If true, then debug messages will be written to the log.
	 */
	static void SetShowDebug(bool showDebug);

private:
	static const std::string SDK_3D_TAG;

	static std::atomic<bool> _ShowError;
	static std::atomic<bool> _ShowWarn;
	static std::atomic<bool> _ShowInfo;
	static std::atomic<bool> _ShowDebug;
};

}

#endif
