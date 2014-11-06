import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents

import org.kde.plasma.private.steam 0.1 as Steam

Item {
	id: global
	
	readonly property int widthSmall: 184
	readonly property int heightSmall: 69
	readonly property int widthBig: 460
	readonly property int heightBig: 215
	
	Plasmoid.switchWidth: widthSmall - 1
	Plasmoid.switchHeight: heightSmall - 1
	
	Plasmoid.fullRepresentation: Item {
		property bool big: (width >= 460 && height >= 215)
		
		GridView {
			id: list
			readonly property int itemWidth:  (big ? widthBig : widthSmall)
			readonly property int itemHeight: (big ? heightBig : heightSmall)
			//we want the maximum gap between items become bigger with the horizontal one but only op to some size.
			//this also determines shadow size
			readonly property int maxVGap: Math.min(cellWidth - itemWidth, itemHeight / 5)
			
			anchors.fill: parent
			
			cellWidth: width / Math.floor(width / itemWidth)
			cellHeight: itemHeight + maxVGap
			
			delegate: Item {
				width:  list.cellWidth
				height: list.cellHeight
				
				RectangularGlow {
					anchors.fill: image
					spread: 0.1
					glowRadius: list.maxVGap / 2
					color: "#80000000"
				}
				
				Image {
					id: image
					anchors.centerIn: parent
					
					source: "http://cdn.akamai.steamstatic.com/steam/apps/" + appID + (big ? "/header.jpg" : "/capsule_184x69.jpg")
					
					width:  list.itemWidth
					height: list.itemHeight
				}
				
				Rectangle {
					anchors.fill: image
					color: theme.viewFocusColor
					opacity: 0
					
					MouseArea {
						anchors.fill: parent
						hoverEnabled: true
						onEntered: {
							parent.opacity = .5
						}
						onExited:  {
							parent.opacity = 0
						}
						onClicked: {
							console.log("Running: steam://run/" + appID)
							backend.openUrl("steam://run/" + appID)
						}
					}
				}
			}
			
			PlasmaComponents.ScrollBar {
				flickableItem: parent
			}
		}
		
		Steam.Backend {
			id: backend
			
			Component.onCompleted: {
				list.model = backend.gamesModel
			}
		}
	}
}
