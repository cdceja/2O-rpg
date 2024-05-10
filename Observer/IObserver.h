#ifndef RPG_IOBSERVER_H
#define RPG_IOBSERVER_H
#include <string>

class IObserver {
	public:
		virtual ~IObserver(){};
		virtual void Update(const std::string &messageFromSubject) = 0;
};
#endif //RPG_IOBSERVER_H
