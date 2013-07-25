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

class ENoServerAvailable : public IException
{

};

class EInvalidCommandReceived : public IException
{

};


#endif /* EXCEPTIONS_H_ */
