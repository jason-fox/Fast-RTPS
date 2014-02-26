/*************************************************************************
 * Copyright (c) 2013 eProsima. All rights reserved.
 *
 * This copy of FastCdr is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/*
 * Participant.h
 *
 *  Created on: Feb 25, 2014
 *      Author: Gonzalo Rodriguez Canosa
 *      email:  gonzalorodriguez@eprosima.com
 */

#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>


#include "rtps_all.h"
#include "ThreadListen.h"
#include "ThreadSend.h"




#ifndef PARTICIPANT_H_
#define PARTICIPANT_H_

namespace eprosima {
namespace rtps {

class StatelessWriter;
class RTPSReader;
class RTPSWriter;
class Endpoint;

/**
 * Class Participant, it contains all the entities and allows the creation and removal of writers and readers. It manages the send and receive threads.
 */
class Participant {
public:
	Participant();
	virtual ~Participant();
	/**
	 * Create a StatelessWriter from a parameter structure.
	 * @param SWriter Pointer to the stateless writer.
	 * @param Wparam Parameters to use in the creation.
	 * @return True if succeeded.
	 */
	bool createStatelessWriter(StatelessWriter* SWriter, WriterParams_t Wparam);
	//bool createStatefulWriter(StatefulWriter*);
	//bool createStatelessReader(RTPSReader*);
	//bool createStetefulReader(StatefulReader* Reader)

	bool removeEndpoint(Endpoint* endpoint);

	ProtocolVersion_t protocolVersion;
	VendorId_t vendorId;
	std::vector<Locator_t> defaultUnicastLocatorList;
	std::vector<Locator_t> defaultMulticastLocatorList;
	GUID_t guid;

	ThreadSend threadSend;

private:
	std::vector<RTPSWriter*> writerList;
	std::vector<RTPSReader*> readerList;
	std::vector<ThreadListen> threadListenList;
	bool assignEnpointToListenThreads(Endpoint* endpoint,char type);
	bool addNewListenThread(Locator_t loc,ThreadListen* listenthread);
};

} /* namespace rtps */
} /* namespace eprosima */

#endif /* PARTICIPANT_H_ */
