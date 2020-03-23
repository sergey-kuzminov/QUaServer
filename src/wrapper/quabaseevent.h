#ifndef QUABASEEVENT_H
#define QUABASEEVENT_H

// NOTE : this define needs to be out of UA_ENABLE_SUBSCRIPTIONS_EVENTS
//        otherwise we don't know if UA_ENABLE_SUBSCRIPTIONS_EVENTS is defined
#include <QUaBaseObject>

#ifdef UA_ENABLE_SUBSCRIPTIONS_EVENTS

// Part 5 - 6.4 : BaseEventType
/*
This EventType is defined in Part 3 (see Part 3 - 4.6 : Event Model). Its representation in the AddressSpace is formally
defined in Table 23 (of Part 5).
HasProperty | Variable | EventId     | ByteString       | PropertyType | Mandatory
HasProperty | Variable | EventType   | NodeId           | PropertyType | Mandatory
HasProperty | Variable | SourceNode  | NodeId           | PropertyType | Mandatory
HasProperty | Variable | SourceName  | String           | PropertyType | Mandatory
HasProperty | Variable | Time        | UtcTime          | PropertyType | Mandatory
HasProperty | Variable | ReceiveTime | UtcTime          | PropertyType | Mandatory
HasProperty | Variable | LocalTime   | TimeZoneDataType | PropertyType | Optional
HasProperty | Variable | Message     | LocalizedText    | PropertyType | Mandatory
HasProperty | Variable | Severity    | UInt16           | PropertyType | Mandatory
*/

#include <QUaProperty>

/*
From open62541 :
It is not necessary to define the attributes `EventId`, `ReceiveTime`, `SourceNode` or `EventType` 
since these are set automatically by the server.
*/

class QUaBaseEvent : public QUaBaseObject
{
    Q_OBJECT

friend class QUaServer;
friend class QUaNode;
friend class QUaBaseObject;

protected:
	// list for known children (standard instance declarations)
	static const QStringList mandatoryChildrenBrowseNames();

public:
	// NOTE : Q_INVOKABLE removed on purpose because this class should not be instantiable
	explicit QUaBaseEvent(
		QUaServer *server,
		const MC& mandatoryChildren = &QUaBaseEvent::mandatoryChildrenBrowseNames
	);

	// Event Properties API

	// Generated by the server to identify a particular *Event Notification*. 
	// The server is responsible to ensure the id is unique.
	QByteArray eventId() const;
	// Specific type of the event.
	QString eventType() const;
	// Node that the Event originated from. If is not specific to a Node, then is set to null. 
	QString sourceNode() const;
	// Description of the source of the Event.
	QString sourceName() const;
	void setSourceName(const QString &strSourceName);
	// Time (in UTC) the Event occurred. It comes from the underlying system or device.
	QDateTime time() const;
	void setTime(const QDateTime &dateTime);
	// Time (in UTC) the OPC UA Server received the Event from the underlying device of another Server (ServerTimestamp).
	QDateTime receiveTime() const;
/*
	// NOTE : removed because is optional and open62541 now does not add it
	// TimeZone of the time the Event occurred.
	QTimeZone localTime() const;
	void setLocalTime(const QTimeZone &localTimeZone);
*/
	// Human-readable description of the Event.
	QString message() const;
	void setMessage(const QString &strMessage);
	// Urgency of the Event. Value from 1 to 1000, with 1 being the lowest severity and 1000 being the highest. 
	// A severity of 1 indicates an Event is informational, while 1000 would indicates catastrophic nature.
	quint16 severity() const;
	void setSeverity(const quint16 &intSeverity);

	// Custom Event API

	// Triggers the event and updates eventId, sourceNode, eventType and receiveTime
	void trigger();

private:
	// ByteString : 
	QUaProperty  * getEventId();
	// NodeId : 
	QUaProperty  * getEventType();
	// NodeId : 
	QUaProperty  * getSourceNode();
	// String : 
	QUaProperty  * getSourceName();
	// UtcTime :   
	QUaProperty  * getTime();
	// UtcTime : 
	QUaProperty  * getReceiveTime();
	// TimeZoneDataType : Offset and the DaylightSavingInOffset flag. 
	//                    Offset specifies the difference (in minutes) between the Time Property 
	//                    and the time at the location in which the event was issued.
	//                    If DaylightSavingInOffset is TRUE, then Daylight savings is in effect and Offset includes the correction.
	//                    If FALSE then the Offset does not include DST correction and DST may or may not have been in effect.
	QUaProperty  * getLocalTime();
	// LocalizedText : 
	QUaProperty  * getMessage();
	// UInt16 : 
	QUaProperty  * getSeverity();

	// Used to trigger the event
	UA_NodeId m_nodeIdOriginator;
	// EventId of last triggered event
	UA_ByteString m_outEventId;

};

#endif // UA_ENABLE_SUBSCRIPTIONS_EVENTS

#endif // QUABASEEVENT_H