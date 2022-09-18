#include "./Callback.hpp"

#pragma once
typedef unsigned short State;
typedef unsigned short Port;

const Port DEFAULT_PORT = 5621;

const State STATE_ERROR = 0;
const State STATE_STOPPED = 1;
const State STATE_STARTED = 2;
const State STATE_STARTING = 3;
const State STATE_STOPPING = 4;