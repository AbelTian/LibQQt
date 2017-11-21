#include <QCoreApplication>

#include <GumboQueryDocument.h>
#include <GumboQuerySelection.h>
#include <GumboQueryNode.h>

void test_parser()
{
    std::string page ( "<h1><a>wrong link</a><a class=\"special\"\\>some link</a></h1>" );
    GumboQueryDocument doc;
    doc.parse ( page.c_str() );

    GumboQuerySelection c = doc.find ( "h1 a.special" );
    GumboQueryNode node = c.nodeAt ( 0 );
    printf ( "Node: %s\n", node.text().c_str() );
    std::string content = page.substr ( node.startPos(), node.endPos() - node.startPos() );
    printf ( "Node: %s\n", content.c_str() );
}

void test_html()
{
    std::string page = "<html><div><span>1\n</span>2\n</div></html>";
    GumboQueryDocument doc;
    doc.parse ( page.c_str() );
    GumboQueryNode pNode = doc.find ( "div" ).nodeAt ( 0 );
    std::string content = page.substr ( pNode.startPos(), pNode.endPos() - pNode.startPos() );
    printf ( "Node: #%s#\n", content.c_str() );
}

void test_escape()
{
    std::string page = "<html><div><span id=\"that's\">1\n</span>2\n</div></html>";
    GumboQueryDocument doc;
    doc.parse ( page.c_str() );
    GumboQueryNode pNode = doc.find ( "span[id=\"that's\"]" ).nodeAt ( 0 );
    std::string content = page.substr ( pNode.startPos(), pNode.endPos() - pNode.startPos() );
    printf ( "Node: #%s#\n", content.c_str() );
}

int main ( int argc, char* argv[] )
{
    QCoreApplication a ( argc, argv );
    test_parser();
    test_html();
    test_escape();

    return 0;
}
