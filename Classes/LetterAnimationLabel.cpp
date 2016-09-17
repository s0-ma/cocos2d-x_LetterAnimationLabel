//
//  LetterAnimationLabel.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/12.
//
//

#include "LetterAnimationLabel.h"

AnimationLabel::AnimationLabel() : RubyLabel(){
    
    //全部一括で表示させる。
    makeAnimation = [this](Sprite* letter,int i, int n_lb){
        FiniteTimeAction* ret = CallFunc::create([this, letter, i](){
            letter->setOpacity(255);
            for(int i_ruby = 0; i_ruby<rubyIndex.size(); i_ruby++){
                if(rubyIndex[i_ruby].parentEnd == i){
                    for(int j_ruby=rubyIndex[i_ruby].rubyStart; j_ruby<rubyIndex[i_ruby].rubyEnd; j_ruby++){
                        rubyLetters->getLetter(j_ruby)->setOpacity(255);
                    }
                }
            }
        });
        return ret;
    };
    
    isRunningFlg = false;
    isPausingFlg = false;
}

AnimationLabel::~AnimationLabel(){
    
}

AnimationLabel* AnimationLabel::createWithTTF(const std::string& text, const std::string& fontFile,
                                              float fontSize, float rubyfontSize,
                                              const Size& dimensions /* = Size::ZERO */,
                                              TextHAlignment hAlignment /* = TextHAlignment::LEFT */,
                                              TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    if(rubyfontSize == 0){
        rubyfontSize = fontSize/2;
    }
    
    auto ret = new (std::nothrow) AnimationLabel();
    
    if (ret && FileUtils::getInstance()->isFileExist(fontFile))
    {
        TTFConfig parentttfConfig(fontFile.c_str(),fontSize,GlyphCollection::DYNAMIC);
        TTFConfig rubyttfConfig(fontFile.c_str(),rubyfontSize,GlyphCollection::DYNAMIC);
        if (ret->parentLetters->setTTFConfig(parentttfConfig) && ret->rubyLetters->setTTFConfig(rubyttfConfig))
        {
            ret->parentLetters->setDimensions(dimensions.width,dimensions.height);
            ret->rubyLetters->setDimensions(dimensions.width,dimensions.height);
            
            ret->setString(text);
            
            ret->parentLetters->setOpacity(0);
            ret->rubyLetters->setOpacity(0);
            
            ret->autorelease();
            
            return ret;
        }
    }
    
    delete ret;
    return nullptr;

}


void AnimationLabel::showAll(){
    stop();
    
    isRunningFlg = false;
    
    int n_lb=0;
    for (int i=0; i<countString(parentLetters->getString()); i++) {
        auto l = parentLetters->getLetter(i+n_lb);
        if(l != NULL){
            l->setOpacity(255);
        }else{
            n_lb++;
            i--;
        }
    }
    for (int j=0; j<countString(rubyLetters->getString()); j++) {
        auto rb = rubyLetters->getLetter(j);
        rb->setOpacity(255);
    }
}

void AnimationLabel::run(){
    clear();
    
    if(isRunning()){
        return;
    }
    
    isRunningFlg = true;
    
    int n_lb=0;
    for (int i=0; i<countString(parentLetters->getString()); i++) {
        auto l = parentLetters->getLetter(i+n_lb);
        if(l != NULL){
            if(i != countString(parentLetters->getString())){
                l->runAction(makeAnimation(l, i, n_lb));
            }else{
                //最後のactionだけは、isRunningFlg用に別処理
                l->runAction(Sequence::create(makeAnimation(l, i, n_lb),
                                              [this](){isRunningFlg = false;},
                                              NULL));
            }
        }else{
            n_lb++;
            i--;
        }
    }
}

void AnimationLabel::stop(){
    isRunningFlg = false;
    
    int n_lb=0;
    for (int i=0; i<countString(parentLetters->getString()); i++) {
        auto l = parentLetters->getLetter(i+n_lb);
        if(l != NULL){
            l->stopAllActions();
        }else{
            n_lb++;
            i--;
        }
    }
    for (int j=0; j<countString(rubyLetters->getString()); j++) {
        auto rb = rubyLetters->getLetter(j);
        rb->stopAllActions();
    }
}

void AnimationLabel::pause(){
    if(!isRunning()){
        return;
    }
    
    isRunningFlg = false;
    isPausingFlg = true;
    
    int n_lb=0;
    for (int i=0; i<countString(parentLetters->getString()); i++) {
        auto l = parentLetters->getLetter(i+n_lb);
        if(l != NULL){
            l->Node::pause();
        }else{
            n_lb++;
            i--;
        }
    }
    for (int j=0; j<countString(rubyLetters->getString()); j++) {
        auto rb = rubyLetters->getLetter(j);
        rb->Node::pause();
    }
}

void AnimationLabel::restart(){
    if(!isPausing()){
        return;
    }
  
    isRunningFlg = true;
    isPausingFlg = false;
    
    int n_lb=0;
    for (int i=0; i<countString(parentLetters->getString()); i++) {
        auto l = parentLetters->getLetter(i+n_lb);
        if(l != NULL){
            l->Node::resume();
        }else{
            n_lb++;
            i--;
        }
    }
    for (int j=0; j<countString(rubyLetters->getString()); j++) {
        auto rb = rubyLetters->getLetter(j);
        rb->Node::resume();
    }
}

void AnimationLabel::clear(){
    stop();
    
    isRunningFlg = false;
    
    int n_lb=0;
    for (int i=0; i<countString(parentLetters->getString()); i++) {
        auto l = parentLetters->getLetter(i+n_lb);
        if(l != NULL){
            l->setOpacity(0);
        }else{
            n_lb++;
            i--;
        }
    }
    for (int j=0; j<countString(rubyLetters->getString()); j++) {
        auto rb = rubyLetters->getLetter(j);
        rb->setOpacity(0);
    }
};

//void AnimationLabel::clearText(){
//};
//void AnimationLabel::setText(const std::string &text){
//    
//};
//void AnimationLabel::addText(std::string text){
//    
//};
//void AnimationLabel::setTexts(std::vector<std::string> texts){
//    
//};

bool AnimationLabel::isRunning(void){
	return isRunningFlg;
};

bool AnimationLabel::isPausing(void){
	return isPausingFlg;
};

void AnimationLabel::setOnEndsCallback(std::function<void(void)> callback){
   
};
void AnimationLabel::setOnLineEndsCallback(std::function<void(void)> callback){
    
};
void AnimationLabel::setOnParagraphEndsCallback(std::function<void(void)> callback){
    
};

//---------------------------------------------------------------------------------------------------------------

TypewriterLabel::TypewriterLabel() : AnimationLabel(){
    
    delayTime = 0.5;//適当なデフォルト値。
    
    makeAnimation = [this](Sprite* letter,int i, int n_lb){
        auto delay = DelayTime::create((i)*delayTime);
        auto cutin = CallFunc::create([this, letter, i,n_lb](){
            //親文字の処理
            letter->setOpacity(255);
            //ルビの処理
            for(int i_ruby = 0; i_ruby<rubyIndex.size(); i_ruby++){
                //親文字が全て表示されたら一括でルビを表示する
                if(rubyIndex[i_ruby].parentEnd == i+n_lb){
                    for(int j_ruby=rubyIndex[i_ruby].rubyStart; j_ruby<rubyIndex[i_ruby].rubyEnd; j_ruby++){
                        rubyLetters->getLetter(j_ruby)->setOpacity(255);
                    }
                }
            }
        });
        auto sequence = Sequence::create(delay, cutin, NULL);
        return sequence;
    };

}
TypewriterLabel::~TypewriterLabel(){
}
TypewriterLabel* TypewriterLabel::createWithTTF(const std::string& text, const std::string& fontFile,
                                                float fontSize, float rubyfontSize,
                                                const Size& dimensions /* = Size::ZERO */,
                                                TextHAlignment hAlignment /* = TextHAlignment::LEFT */,
                                                TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    if(rubyfontSize == 0){
        rubyfontSize = fontSize/2;
    }
    
    auto ret = new (std::nothrow) TypewriterLabel();
    
    if (ret && FileUtils::getInstance()->isFileExist(fontFile))
    {
        TTFConfig parentttfConfig(fontFile.c_str(),fontSize,GlyphCollection::DYNAMIC);
        TTFConfig rubyttfConfig(fontFile.c_str(),rubyfontSize,GlyphCollection::DYNAMIC);
        if (ret->parentLetters->setTTFConfig(parentttfConfig) && ret->rubyLetters->setTTFConfig(rubyttfConfig))
        {
            ret->parentLetters->setDimensions(dimensions.width,dimensions.height);
            ret->rubyLetters->setDimensions(dimensions.width,dimensions.height);
            
            ret->setString(text);
            
            ret->parentLetters->setOpacity(0);
            ret->rubyLetters->setOpacity(0);
            
            ret->autorelease();
            
            return ret;
        }
    }
    
    delete ret;
    return nullptr;
    
}

void TypewriterLabel::setDelayTime(double delayTime){
    this->delayTime = delayTime;
};

void TypewriterLabel::runWithDelayTime(double delayTime){
    setDelayTime(delayTime);
    run();
};


FadeinLabel::FadeinLabel() : AnimationLabel(){
    
    delayTime = 0.5;
    fadeinTime = 0.5;
    
    makeAnimation = [this](Sprite* letter,int i, int n_lb){
        auto delay = DelayTime::create((i)*delayTime);
        //親文字の処理
        auto fadein = FadeIn::create(fadeinTime);
        //ルビ
        auto cutin = CallFunc::create([this, letter, i,n_lb](){
            //ルビの処理
            for(int i_ruby = 0; i_ruby<rubyIndex.size(); i_ruby++){
                //親文字が全て表示されたら一括でルビを表示する
                if(rubyIndex[i_ruby].parentStart == i+n_lb){
                    for(int j_ruby=rubyIndex[i_ruby].rubyStart; j_ruby<rubyIndex[i_ruby].rubyEnd; j_ruby++){
                        rubyLetters->getLetter(j_ruby)->runAction(FadeIn::create(fadeinTime));
                    }
                }
            }
        });
        auto sequence = Sequence::create(delay, cutin, fadein, NULL);
        return sequence;
    };
    
}
FadeinLabel::~FadeinLabel(){
}
FadeinLabel* FadeinLabel::createWithTTF(const std::string& text, const std::string& fontFile,
                                                float fontSize, float rubyfontSize,
                                                const Size& dimensions /* = Size::ZERO */,
                                                TextHAlignment hAlignment /* = TextHAlignment::LEFT */,
                                                TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    if(rubyfontSize == 0){
        rubyfontSize = fontSize/2;
    }
    
    auto ret = new (std::nothrow) FadeinLabel();
    
    if (ret && FileUtils::getInstance()->isFileExist(fontFile))
    {
        TTFConfig parentttfConfig(fontFile.c_str(),fontSize,GlyphCollection::DYNAMIC);
        TTFConfig rubyttfConfig(fontFile.c_str(),rubyfontSize,GlyphCollection::DYNAMIC);
        if (ret->parentLetters->setTTFConfig(parentttfConfig) && ret->rubyLetters->setTTFConfig(rubyttfConfig))
        {
            ret->parentLetters->setDimensions(dimensions.width,dimensions.height);
            ret->rubyLetters->setDimensions(dimensions.width,dimensions.height);
            
            ret->setString(text);
            
            ret->parentLetters->setOpacity(0);
            ret->rubyLetters->setOpacity(0);
            
            ret->autorelease();
            
            return ret;
        }
    }
    
    delete ret;
    return nullptr;
    
}

void FadeinLabel::setDelayTime(double delayTime){
    this->delayTime = delayTime;
};
void FadeinLabel::setFadeinTime(double fadeinTime){
    this->fadeinTime = fadeinTime;
};
void FadeinLabel::runWithDelayFadeinTime(double delayTime, double fadeinTime){
    setDelayTime(delayTime);
    setFadeinTime(fadeinTime);
    run();
};

