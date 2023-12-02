#pragma once
#include <iostream>
#include <boost/process.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>

namespace bp = boost::process;
namespace bio = boost::iostreams;

namespace BOOST {
	class IPC_PIPE {
	private: 
		bp::opstream in;
		bp::ipstream out;
		bp::child c;
		boost::asio::io_context io_context_;
		boost::asio::streambuf buffer_;
	public: 
		IPC_PIPE();
		~IPC_PIPE();
		void write(std::string input);
		std::vector<std::string> read();
	};
}