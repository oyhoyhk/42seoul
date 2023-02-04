#ifndef CHANNELMANAGER_HPP
#define CHANNELMANAGER_HPP

#include "header.hpp"
#include "Channel/Channel.hpp"

class ChannelManager {
private:
	typedef map<string, Channel*>::const_iterator channel_const_iter;
	typedef map<string, Channel*>::iterator channel_iter;
	map<string, Channel*>		_channels;
public:
	~ChannelManager(void);
	Channel*	getChannelWithName(const string& name) const;
	void		addChannel(const string& name);
	void		deleteChannel(const string& name);
	void		partUserFromChannels(const string& user_name, const vector<string>& channels);
};

#endif
