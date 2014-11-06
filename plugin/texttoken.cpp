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

#include "texttoken.h"

#include <QDebug>

/**
 * Needs line starting with "token", {, or }.
 */
QPair<QString, int> readToken(const QString & line, int start = 0) {
	int first = line.indexOf('"', start);
	int last = line.indexOf('"', first + 1);
	
	QString res;
	if (last != -1) {
		res = line.mid(first + 1, last - first - 1);
	} else {
		res = line.mid(start, 1);
		if (!res.isEmpty()) {
			last = 0;
		} else {
			res = QString();
			last = -2;
		}
	}
	
	return QPair<QString, int>(res, last + 1);
}

TextToken::TextToken(QTextStream & stream, const QString & key): key(key) {
	while (!stream.atEnd()) {
		QString line = stream.readLine().trimmed();
		
		QPair<QString, int> t = readToken(line);
		QString token = t.first;
		int afterToken = t.second;
		
// 		qDebug() << "line, TPos:" << line << afterToken;
// 		qDebug() << "Token:" << token;
		
		if(token == "}")
			break;
		
		QString value = readToken(line, afterToken).first;
		
// 		qDebug() << "Value:" << value;
		
		if (value.isEmpty()) {
			line = stream.readLine().trimmed();
			value = readToken(line).first;
		}
		
// 		qDebug() << "New Value:" << value;
		
		if (token == key) {
			continue;
		} else if (value == "{") {
			children.insert(token, QSharedPointer<TextToken>::create(stream, t.first));
		} else {
			values.insert(token, value);
		}
	} 
}

QString TextToken::getKey() { return key; }

QSharedPointer<TextToken> TextToken::getToken(const QString & key) {
	TokenIterator itr = children.find(key);
	if(itr == children.end())
		return QSharedPointer<TextToken>();
	return itr.value();
}

QList<QSharedPointer<TextToken>> TextToken::getAllTokens(const QString & key) {
	return children.values(key);
}

QList<QSharedPointer<TextToken>> TextToken::getAllTokens() {
	return children.values();
}

QSharedPointer<TextToken> TextToken::getTokenFromPath(const QString & path, QChar separator) {   
	QSharedPointer<TextToken> ret;
	int pidx, idx = path.indexOf(separator);
	if(idx == -1)
		return ret;
	ret = getToken(path.left(idx));
	pidx = idx;
	while ((idx = path.indexOf(separator, idx + 1)) < path.size() && ret) {
		ret = ret->getToken(path.mid(++pidx, idx - pidx));
		pidx = idx;
	}
	if (++pidx < path.size() && ret) {
		ret = ret->getToken(path.mid(pidx));
	}
	return ret;
}

QString TextToken::getValue(const QString & key) {
	ValueIterator itr = values.find(key);
	if(itr == values.end())
		return QString();
	return itr.value();
}

QList<QString> TextToken::getAllValues(const QString & key) {
	return values.values(key);
}

bool TextToken::serialize(QTextStream& stream, const QString & tabs) {
	if(stream.atEnd())
		return false;
	stream << tabs << '\"' << this->key << '\"' << endl << tabs << "{" << endl;
	for(ValueIterator itr = values.begin(); itr != values.end(); ++itr) {
		stream << (tabs + '\t') << '\"' << itr.key() << '\"' << "\t\t\"" << itr.value() << '\"' << endl;
	}
	for(TokenIterator itr = children.begin(); itr != children.end(); ++itr) {
		if(itr.value()->serialize(stream, tabs + '\t') == false)
			return false;
	}
	stream << tabs << "}" << endl;
	return !stream.atEnd();
}

//adds a token using the specified key
void TextToken::addToken(const QString & key, QSharedPointer<TextToken> token) {
	children.insert(key, token);
}

//replaces the token at the specified key
void TextToken::setToken(const QString & key, QSharedPointer<TextToken> token) {
	TokenIterator itr = children.find(key);
	if(itr != children.end()) {
		itr.value() = token;
	}
}