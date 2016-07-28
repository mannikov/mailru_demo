#include <iostream>
#include <Poco/Net/MessageHeader.h>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/POP3ClientSession.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/Context.h>
#include <Poco/AutoPtr.h>
#include <Poco/Path.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/ConsoleCertificateHandler.h>
#include <Poco/Net/AcceptCertificateHandler.h>

using namespace std;
using namespace Poco::Net;
using namespace Poco;

int main(int argc, char *argv[])
{
	// check parameters
	if (argc != 3)
	{
		Path p(argv[0]);
		cerr << "usage: " << p.getBaseName() << " email password" << endl;
		cerr << "       List all emails from mailbox." << endl;
		return 1;
	}

	// mail.ru settings
	string host = "pop.mail.ru";
	int port = 995;
	// user and password
	string user(argv[1]);
	string pass(argv[2]);
	try {
		// init SSL
		initializeSSL();
		// always accept even if error occurred
		SharedPtr<InvalidCertificateHandler> ptrHandler = new AcceptCertificateHandler(false);
		Context::Ptr ptrContext = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_NONE, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
		SSLManager::instance().initializeClient(0, ptrHandler, ptrContext);
		SocketAddress socketAddress(host, port);
		cout << "Connecting..." << endl;
		SecureStreamSocket socket(socketAddress, ptrContext);
		POP3ClientSession session(socket);

		// login
		cout << "Logging in..." << endl;
		session.login(user, pass);
		POP3ClientSession::MessageInfoVec messages;

		// list all the messages
		cout << "Loading messages..." << endl;
		session.listMessages(messages);
		for (auto i = messages.begin(); i != messages.end(); ++i) {
			MessageHeader header;
			session.retrieveHeader((*i).id, header);
			cout << endl
				<< "ID: " << (*i).id << ", "
				<< "Size: " << (*i).size << " bytes" << endl
				<< "From: " << header.get("From") << endl
				<< "Subject: " << header.get("Subject") << endl
				<< "Date: " << header.get("Date") << endl;
		}

		// finalize
		session.close();
		uninitializeSSL();
	}
	catch (POP3Exception &e) {
		cerr << e.displayText() << endl;
		uninitializeSSL();
	}
	catch (NetException &e) {
		cerr << e.displayText() << endl;
		uninitializeSSL();
	}
	return 0;
}