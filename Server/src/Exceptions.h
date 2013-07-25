/*
 * Exceptions.h
 *
 *  Created on: Apr 28, 2013
 *      Author: kostya
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

class IException
{

};


class EConnectionFailed : public IException
{

};

class EConnectionFailedFirst : public EConnectionFailed
{

};

class EConnectionFailedSecond : public EConnectionFailed
{

};


class EInvalidDataReceived : public IException
{

};

class ELogicException : public IException
{

};

class ENoPortsAvailable : public EConnectionFailed
{

};


#endif /* EXCEPTIONS_H_ */
