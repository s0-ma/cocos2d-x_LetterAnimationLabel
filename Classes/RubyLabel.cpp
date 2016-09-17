//
//  RubyLabel.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/18.
//
//

#include <regex>

#include "RubyLabel.h"

RubyLabel::RubyLabel(){
    
    parentLetters = Label::create();
    parentLetters->setAnchorPoint(Vec2(0,1));
    parentLetters->setPosition(Vec2(0,0));
    this->addChild(parentLetters,0,0);
    
    rubyLetters = Label::create();
    rubyLetters->setAnchorPoint(Vec2(0,0));
    rubyLetters->setPosition(Vec2(0,0));
    this->addChild(rubyLetters,0,1);
    
    fullText = "";
    
};
RubyLabel::~RubyLabel(){
}

RubyLabel* RubyLabel::createWithTTF(const std::string& text, const std::string& fontFile,
                                    float fontSize, float rubyfontSize,
                                    const Size& dimensions /* = Size::ZERO */,
                                    TextHAlignment hAlignment /* = TextHAlignment::LEFT */,
                                    TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    if(rubyfontSize == 0){
        rubyfontSize = fontSize/2;
    }
    
    auto ret = new (std::nothrow) RubyLabel();
    
    if (ret && FileUtils::getInstance()->isFileExist(fontFile))
    {
        TTFConfig parentttfConfig(fontFile.c_str(),fontSize,GlyphCollection::DYNAMIC);
        TTFConfig rubyttfConfig(fontFile.c_str(),rubyfontSize,GlyphCollection::DYNAMIC);
        if (ret->parentLetters->setTTFConfig(parentttfConfig) && ret->rubyLetters->setTTFConfig(rubyttfConfig))
        {
            ret->parentLetters->setDimensions(dimensions.width,dimensions.height);
            ret->rubyLetters->setDimensions(dimensions.width,dimensions.height);
            
            ret->setString(text);
            
            ret->autorelease();
            
            return ret;
        }
    }
    
    delete ret;
    return nullptr;
}

int RubyLabel::countByte(unsigned char cChar){
    int iByte;
    
    if ((cChar >= 0x00) && (cChar <= 0x7f)) {
        iByte = 1;
    } else if ((cChar >= 0xc2) && (cChar <= 0xdf)) {
        iByte = 2;
    } else if ((cChar >= 0xe0) && (cChar <= 0xef)) {
        iByte = 3;
    } else if ((cChar >= 0xf0) && (cChar <= 0xf7)) {
        iByte = 4;
    } else if ((cChar >= 0xf8) && (cChar <= 0xfb)) {
        iByte = 5;
    } else if ((cChar >= 0xfc) && (cChar <= 0xfd)) {
        iByte = 6;
    } else {
        iByte = 0;
    }
    
    return iByte;
}

int RubyLabel::countString(const std::string text)
{
    int i = 0;
    int iCnt = 0;
    
    while (text[i] != '\0') {
        iCnt++;
        i += countByte(text[i]);
    }
    
    return iCnt;
}


void RubyLabel::setString(const std::string& text)
{
    
    CCLOG("%d",text.compare(fullText));
    //    if (text.compare(fullText))
    if (1){
        fullText = text;
        parentText = "";
        rubyText = "";
        rubyIndex.clear();
        
        //青空記法のルビ表記の探索
        std::regex pattern("\\|(.+?)<<(.*?)>>");
        std::smatch sm;
        auto it = text.begin();
        //sm.position(0) : |kanji<<hurigana>>
        //sm.position(1) : kanji
        //sm.position(2) : hurigana
        
        for (int i=0; regex_search( it, text.end(), sm, pattern ); it += sm.position(0) + sm.length(0) ){
            rubyIndex.push_back(RubyIndex());
            auto prev_index = it-text.begin();
            parentText += text.substr(prev_index, sm.position(0));
//            CCLOG("base text: %s", sm.str(1).c_str());
//            CCLOG("base index:%d", countString(parentText));
            rubyIndex[i].parentStart = countString(parentText);
//            CCLOG("base len : %d", countString(sm.str(1)));
            rubyIndex[i].parentEnd = countString(parentText)+countString(sm.str(1))-1;
            
            parentText += text.substr(prev_index+sm.position(1), sm.length(1));
//            CCLOG("ruby text: %s", sm.str(2).c_str());
            rubyIndex[i].rubyStart = countString(rubyText);
            rubyText += sm.str(2);
//            CCLOG("ruby len : %d", countString(sm.str(2)));
            rubyIndex[i].rubyEnd = countString(rubyText);
            
            i++;
        }
        parentText += text.substr(it-text.begin(), text.end()-it);
        
        this->parentLetters->setString(parentText);
        this->rubyLetters->setString(rubyText);
        
        adjustRubyPosition();
        
    }
}

void RubyLabel::setColor(const cocos2d::Color3B &color){
    //初回getLetter()の際に、それまでの設定がキャンセルされるバグが有り。
    //回避のため、始めに取りあえず全ての文字に関してgetLetterしてしまう。
    for (int i=0; i<countString(parentLetters->getString()); i++) {
        parentLetters->getLetter(i);
    }
    
    this->parentLetters->setColor(color);
    this->rubyLetters->setColor(color);
}

void RubyLabel::adjustRubyPosition(){
    parentLetters->removeAllChildrenWithCleanup(true);
    rubyLetters->removeAllChildrenWithCleanup(true);
    
    //rubyの位置調整
    for(int i=0; i<rubyIndex.size(); i++){
        //改行に伴う空白文字の処理
//        int n_lb = 0;
//        for(int k=0; k<rubyIndex[i].parentStart; k++){
//            if(parentLetters->getLetter(k) == NULL){
//                n_lb ++;
//            }
//        }
//        rubyIndex[i].parentStart += n_lb;
//        rubyIndex[i].parentEnd += n_lb;
        
        //ルビ位置の計算
//        CCLOG("%d, %d", rubyIndex[i].parentStart,rubyIndex[i].parentEnd);
        auto widthl = parentLetters->getLetter(rubyIndex[i].parentStart)->getContentSize().width;
        auto widthr = parentLetters->getLetter(rubyIndex[i].parentEnd)->getContentSize().width;
        auto pXl = parentLetters->getLetter(rubyIndex[i].parentStart)->getPositionX() - widthl/2;
        //        CCLOG("%f",pXl);
        auto pXr = parentLetters->getLetter(rubyIndex[i].parentEnd)->getPositionX() + widthr/2;
        //        CCLOG("%f",pXr);
        auto rubyLen = rubyIndex[i].rubyEnd-rubyIndex[i].rubyStart;
        //        CCLOG("%d", rubyLen);
        
        //ルビの配置
        for(int j=0; j<rubyLen; j++){
            auto l = rubyLetters->getLetter(rubyIndex[i].rubyStart+j);
            l->setPositionX(pXl + (pXr-pXl)/(rubyLen-1 +1) * (j+1./2));
            l->setPositionY(-(parentLetters->getContentSize().height)
                            + parentLetters->getLetter(rubyIndex[i].parentStart)->getPositionY()
                            + parentLetters->getTTFConfig().fontSize * 0.8);
            //            CCLOG("let ind %d", rubyIndex[i].rubyStart+j);
            //            CCLOG("let pos x%f", pXl + (pXr-pXl)/(rubyLen+1) * (j+1));
            //            CCLOG("let pos y%f", parentLetters->getLetter(rubyIndex[i].parentStart)->getPositionY()
            //                  + parentLetters->getTTFConfig().fontSize * 0.8);
        }
    }
    
    
}

void RubyLabel::setLineHeight(float s){
    parentLetters->setLineHeight(s);
    //    adjustRubyPosition();
}

void RubyLabel::setMaxLineWidth(unsigned int maxLineWidth){
    parentLetters->setMaxLineWidth(maxLineWidth);
    //    adjustRubyPosition();
}

Size RubyLabel::getContentSize(){
    return parentLetters->getContentSize();
}


