import QtQuick 2.15
import QtQuick.Particles 2.0
import QtQuick.Window 2.15

Window {
    width: 1920 / 2
    height: 1080 / 2
    visible: true
    title: qsTr("Hello World")
    color: "red" // test
    property var gameState
    property bool passedSplash: false

    ParticleSystem {
        id: particles
        anchors.fill: parent

        ImageParticle {
            id: bubble
            anchors.fill: parent
            source: "../resource/gfx/catch.png"
            opacity: 1
        }

        Wander {
            xVariance: 40;
            pace: 30;
        }

        Emitter {
            width: parent.width
            height: 150
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 3
            startTime: 15000

            emitRate: 2
            lifeSpan: 15000

            acceleration: PointDirection{ y: -6; xVariation: 2; yVariation: 2 }

            size: 24
            sizeVariation: 16
        }
    }


}
