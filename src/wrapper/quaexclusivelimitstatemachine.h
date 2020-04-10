#ifndef QUAEXCLUSIVELIMITSTATEMACHINE_H
#define QUAEXCLUSIVELIMITSTATEMACHINE_H

#include <QUaFiniteStateMachine>

#ifdef UA_ENABLE_SUBSCRIPTIONS_ALARMS_CONDITIONS

// Part 9 - 5.8.12.2
/*


*/

class QUaExclusiveLimitStateMachine : public QUaFiniteStateMachine
{
    Q_OBJECT

public:
	Q_INVOKABLE explicit QUaExclusiveLimitStateMachine(
		QUaServer* server
	);


protected:


};

#endif // UA_ENABLE_SUBSCRIPTIONS_ALARMS_CONDITIONS

#endif // QUAEXCLUSIVELIMITSTATEMACHINE_H

