/**
 * \file testhello.cpp
 * \date Apr 14, 2010
 * \author samael
 */

#include <iostream>
#include <CDirector.h>
#include <AActor.h>
#include <CSimpleWorkflowExecutor.h>

using namespace std;
using namespace wfe;

class HelloActor: public AActor
{
public:
	HelloActor(): _state(READY) {}
	State state() { return _state; }
	void fire() { cout << "Hello World!" << endl; }
	void wrapup() { _state = FINISHED; }

private:
	State _state;
};

int main()
{
	CSimpleWorkflowExecutor exec;
	CDirector d(&exec);
	HelloActor hello;

	d.addActor(&hello);
	d.execute();

	return 0;
}
