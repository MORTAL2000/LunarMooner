﻿/*********************************************************************
Matt Marchant 2016
http://trederia.blogspot.com

Lunar Mooner Map Editor - Zlib license.

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.
*********************************************************************/

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Input;

using Newtonsoft.Json;

namespace MapEditor
{
    /// <summary>
    /// Contains functions for read / writing json files
    /// </summary>
    public partial class MainWindow : Form
    {
        private string m_currentPath = "";

        public class Point
        {
            public float X;
            public float Y;
            public Point()
            {
                X = 0;
                Y = 0;
            }
            public Point(float x, float y)
            {
                X = x;
                Y = y;
            }
        }

        public class Platform
        {
            public Point Position { get; set; }
            public Point Size { get; set; }
            public int Value { get; set; }
            public Platform(Point position, Point size, int value)
            {
                Position = position;
                Size = size;
                Value = value;
            }
            public Platform()
            {
                Value = 10;
                Position = new Point();
                Size = new Point();
            }
        }

        public class MapDefinition
        {
            public string TextureName { get; set; }
            public List<Platform> Platforms { get; set; }
            public List<Point> Points { get; set; }
            public float WaterLevel { get; set; }
            public MapDefinition()
            {
                TextureName = "";
                Platforms = new List<Platform>();
                Points = new List<Point>();
                WaterLevel = 0;
            }
        }

        private void SaveFile(string path)
        {
            MapDefinition mapDef = new MapDefinition();
            if (listBoxTextures.Items.Count > 0)
            {
                mapDef.TextureName = listBoxTextures.GetItemText(listBoxTextures.Items[0]);
            }

            foreach(var p in m_screenPoints)
            {
                mapDef.Points.Add(new Point(p.Position.X, p.Position.Y));
            }

            foreach (var b in m_screenBoxes)
            {
                mapDef.Platforms.Add(new Platform(new Point(b.Box.Position.X, b.Box.Position.Y), new Point(b.Box.Size.X, b.Box.Size.Y), b.Value));
            }

            mapDef.WaterLevel = (float)numericUpDownWaterLevel.Value;

            try
            {
                JsonSerializer srlz = new JsonSerializer();
                srlz.NullValueHandling = NullValueHandling.Ignore;
                srlz.Formatting = Formatting.Indented;

                using (StreamWriter sw = new StreamWriter(path))
                using (JsonWriter jw = new JsonTextWriter(sw))
                {
                    srlz.Serialize(jw, mapDef);
                }

                m_currentPath = path;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Output failed");
            }
        }

        private void LoadFile(string path)
        {
            try
            {
                MapDefinition md = new MapDefinition();

                JsonSerializer srlz = new JsonSerializer();
                srlz.NullValueHandling = NullValueHandling.Ignore;

                using (StreamReader sr = new StreamReader(path))
                using (JsonReader jr = new JsonTextReader(sr))
                {
                    md = srlz.Deserialize<MapDefinition>(jr);
                }


                ClearAll();

                if(md.TextureName != string.Empty)
                {
                    try
                    {
                        LoadTexture(Path.GetDirectoryName(path) + Path.DirectorySeparatorChar + md.TextureName);
                    }
                    catch(Exception ex)
                    {
                        MessageBox.Show(ex.Message, "Failed Loading Image");
                    }
                }

                foreach(var p in md.Points)
                {
                    m_screenPoints.Add(new ScreenPoint(new SFML.Window.Vector2f(p.X, p.Y)));
                }

                foreach(var b in md.Platforms)
                {
                    m_screenBoxes.Add(new ScreenBox(new SFML.Window.Vector2f(b.Position.X, b.Position.Y)));
                    m_screenBoxes.Last().Box.Size = new SFML.Window.Vector2f(b.Size.X, b.Size.Y);
                    m_screenBoxes.Last().Value = b.Value;
                }

                numericUpDownWaterLevel.Value = (decimal)md.WaterLevel;

                m_currentPath = path;
            }
            catch(Exception e)
            {
                MessageBox.Show(e.Message, "Failed to open map file");
            }
        }
    }
}