#ifndef RPG_ISUBJECT_H
#define RPG_ISUBJECT_H
#include "IObserver.h"
#include <string>

class ISubject {
	public:
		virtual ~ISubject(){};
		virtual void Attach(IObserver*) = 0;
		virtual void Detach(IObserver*) = 0;
		virtual void Notify(std::string) = 0;
};
#endif //RPG_ISUBJECT_H
