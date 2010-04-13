//#ifndef RUNNERAGENT_H_
//#define RUNNERAGENT_H_
//
//#include <vector>
//#include <string>
//#include <pthread.h>
//#include <TCPSocket.h>
//#include "AbstractWorkerActor.h"
//
//namespace wfe
//{
//
//class RunnerAgent
//{
//public:
//	typedef enum State {
//		NOT_READY,
//		READY
//	} State;
//	static const char *StateString[];
//	static RunnerAgent* instance();
//	static void release();
//	State state() const { return _state; }
//	const std::vector<cml::TCPSocket *>& runners() const { return _ssocks; }
//	bool setup(unsigned short runner_port, unsigned short master_port, const
//			std::string &appname, unsigned int timeout = 2);
//	bool sendActor(AbstractWorkerActor *actor, cml::TCPSocket *rsock = NULL);
//	bool runActor(cml::TCPSocket *rsock = NULL);
//
//private:
//	RunnerAgent();
//	~RunnerAgent();
//	static RunnerAgent* _instance;
//	static pthread_mutex_t _mutex;
//	State _state;
//	cml::TCPSocket _msock;
//	std::vector<cml::TCPSocket *> _ssocks;
//};
//
//}
//
//#endif /* RUNNERAGENT_H_ */
