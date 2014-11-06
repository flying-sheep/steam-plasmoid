//The MIT License(MIT)
//
//Copyright(c) 2013 Fabian Wahlster - razor@singul4rity.com
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.

#ifndef TEXTTOKEN_H
#define TEXTTOKEN_H

#include <QtCore>

class TextToken {

private:
	QString key; //name
	QMultiMap<QString, QSharedPointer<TextToken>> children;
	QMultiMap<QString, QString> values;
	
	QString read_value(QTextStream & stream, QChar separator = '\"');

public:
	typedef QMultiMap<QString, QSharedPointer<TextToken>>::iterator TokenIterator;
	typedef QMultiMap<QString, QString>::iterator ValueIterator;
	
	//parse key-value from stream
	TextToken(QTextStream & stream, const QString & key);
	
	QString getKey();
	
	//write key-value tree to stream
	bool serialize(QTextStream & stream, const QString & tabs = "");
	
	template <class T> T get(const QString & key) {
		T ret = T();
		ValueIterator itr = values.find(key);
		if(itr == values.end())
			return ret;
		QTextStream stream(&itr.value(), QIODevice::ReadOnly);
		stream >> ret;
		return ret;
	}
	
	template <class T> T getFromPath(const QString & path, QString & key) {
		T ret = T();
		QSharedPointer<TextToken> object = getTokenFromPath(path);
		if(!object)
			return ret;
		return object->get<T>(key);
	}
	
	template <class T> QList<T> getAll(const QString & key) {
		T val = T();
		QList<T> ret;
		QPair<ValueIterator, ValueIterator> itr = values.equal_range(key);
		for(ValueIterator it = itr.first; it != itr.second; ++it) {
			QTextStream stream(it.value(), QIODevice::ReadOnly);
			stream >> val;
			ret.push_back(val);
		}
		return ret;
	}
	
	template <class T> QList<T> getAll() {
		T val = T(); QList<T> ret;
		ValueIterator itr;
		for(itr = values.begin(); itr != values.end(); ++itr) {
			QTextStream stream(itr.value(), QIODevice::ReadOnly);
			stream >> val;
			ret.push_back(val);
		}
		return ret;
	}
	
	template <class T> QList<QPair<T, QString>> getAllPairs() {
		T key = T();
		QList<QPair<T, QString>> ret;
		ValueIterator itr;
		for(itr = values.begin(); itr != values.end(); ++itr) {
			QTextStream stream(itr.key(), QIODevice::ReadOnly);
			stream >> key;
			ret.push_back(QPair<T, QString>(key, itr.value()));
		}
		return ret;
	}
	
	template <class T1, class T2> QList<QPair<T1, T2>> getAllPairs() {
		T1 key = T1();T2 val = T2(); QList<QPair<T1, T2>> ret;
		ValueIterator itr;
		for(itr = values.begin(); itr != values.end(); ++itr) {
			QTextStream stream(itr.key() + ' ' + itr.value(), QIODevice::ReadOnly);
			stream >> key >> val;
			ret.push_back(QPair<T1,T2>(key,val));
		}
		return ret;
	}
	
	//get the raw value data (string) with the corresponding key
	QString getValue(const QString & key);
	
	//get all raw values (string) with the corresponding key
	QList<QString> getAllValues(const QString & key);
	
	//get the child token with the corresponding key
	QSharedPointer<TextToken> getToken(const QString & key);
	
	//get all child tokens with the corresponding key
	QList<QSharedPointer<TextToken>> getAllTokens(const QString & key);
	
	//get all child tokens from this token
	QList<QSharedPointer<TextToken>> getAllTokens();
	
	//get the token using a complete path (e.g. AppState->getTokenFromPath("UserConfig/CheckGuid");
	QSharedPointer<TextToken> getTokenFromPath(const QString & path, QChar separator = '/');
	
	//adds primitive value using the specified key
	
	template <class T> void add(const QString & key, T value) {
		QTextStream ss;
		ss << value;
		values.insert(key, *ss.string());
	}
	
	//replaces the primitive value at the specified key
	template <class T> void set(const QString & key, T value) {
		ValueIterator itr = values.find(key);
		if(itr != values.end()) {
			QTextStream ss;
			ss << value;
			itr.value() = ss.string();
		}
	}
	
	//adds a token using the specified key
	void addToken(const QString & key, QSharedPointer<TextToken> token);
	
	//replaces the token at the specified key
	void setToken(const QString & key, QSharedPointer<TextToken> token);
};

#endif 
