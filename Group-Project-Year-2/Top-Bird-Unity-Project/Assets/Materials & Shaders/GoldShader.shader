Shader "UI/GoldGradientShader"
{
    Properties
    {
        _MainTex("Texture", 2D) = "white" {}
        _Speed("Speed", Range(-5, 5)) = 1
    }
        SubShader
        {
            Tags {"Queue" = "Transparent" "IgnoreProjector" = "True" "RenderType" = "Transparent"}
            LOD 100

            Pass
            {
                Blend SrcAlpha OneMinusSrcAlpha

                CGPROGRAM
                #pragma vertex vert
                #pragma fragment frag
                #include "UnityCG.cginc"

                struct appdata_t
                {
                    float4 vertex   : POSITION;
                    float2 texcoord : TEXCOORD0;
                };

                struct v2f
                {
                    float2 texcoord : TEXCOORD0;
                    float4 vertex   : SV_POSITION;
                };

                sampler2D _MainTex;
                float4 _MainTex_ST;
                float _Speed;

                v2f vert(appdata_t v)
                {
                    v2f o;
                    o.vertex = UnityObjectToClipPos(v.vertex);
                    o.texcoord = TRANSFORM_TEX(v.texcoord, _MainTex);
                    return o;
                }

                fixed4 frag(v2f i) : SV_Target
                {
                    fixed4 baseColor = fixed4(218 / 255.0, 165 / 255.0, 32 / 255.0, 1.0);
                    fixed4 lightColor = fixed4(255 / 255.0, 215 / 255.0, 0 / 255.0, 1.0);

                    float2 texCoord = i.texcoord;
                    float2 center = float2(0.5, 0.5);
                    float2 rotatedTexCoord = float2(
                        (texCoord.x - center.x) * cos(0.38397244) - (texCoord.y - center.y) * sin(0.38397244) + center.x,
                        (texCoord.x - center.x) * sin(0.38397244) + (texCoord.y - center.y) * cos(0.38397244) + center.y
                    );

                    float colorFactor = (sin(rotatedTexCoord.x * 8.0 + _Time.y * _Speed) + 1.0) / 2.0;
                    fixed4 col = lerp(baseColor, lightColor, colorFactor) * tex2D(_MainTex, i.texcoord);
                    return col;
                }
                ENDCG
            }
        }
}